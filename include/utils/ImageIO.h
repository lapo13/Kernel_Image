#ifndef IMAGEIO_H
#define IMAGEIO_H
#include <string>
#include "core/Image.h"
#include "ImageHeader.h"
#include <fstream>
#include <stdlib.h>
#include <typeinfo>
#include <iostream>

namespace ImageIO 
{ 
    template<typename T>
    Image<T>* loadImage(const std::string& filename) {
        ImageHeader header;
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            std::cerr << "Error code: " << strerror(errno) << std::endl;
            exit(1);
        }
        
        // Read header
        file >> header.magicNumber;
        if (header.magicNumber != "P6" && header.magicNumber != "P5") {
            std::cerr << "Error: File not supported " << std::endl;
            file.close();
            return nullptr;
        }

        header.numChannels = header.magicNumber == "P6" ? 3 : 1;
        file >> header.width >> header.height >> header.maxVal;

        
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        
        const size_t bufferSize = header.width * header.height * header.numChannels;
        T* imgBuffer = new T[bufferSize];
        
        if(imgBuffer == nullptr) {
            std::cerr << "Error: Could not allocate memory for buffer of type: " 
                    << typeid(T).name() << std::endl;
            file.close();
            exit(1);
        }

        // Read file data into buffer
        file.read(reinterpret_cast<char*>(imgBuffer), bufferSize * sizeof(T));
        
        if (file.gcount() != (long)(bufferSize * sizeof(T))) {
            std::cerr << "Error: Could not read complete image data of type: " 
                    << typeid(T).name() << ". Expected " 
                    << bufferSize * sizeof(T) << " bytes but got " 
                    << file.gcount() << std::endl;
            delete[] imgBuffer;
            file.close();
            return nullptr;
        }

        file.close();
        
        // Create image with proper type
        Image<T>* img = new Image<T>(imgBuffer, header);
        delete[] imgBuffer;  
        
        return img;
    }

    template<typename T>
    void saveImage(const std::string &filename, Image<T>& image){
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error: Could not create file " << filename << std::endl;
            std::cerr << "Error code: " << strerror(errno) << std::endl;
            return;
        }

        ImageHeader header = image.getHeader();

        // Write header
        file << header.magicNumber << "\n"; 
        file << header.width << " " << header.height << "\n";
        file << header.maxVal << "\n";

        // allocate buffer
        const size_t bufferSize = header.width * header.height * header.numChannels;
        T* buffer = new T[bufferSize];  // Changed to T* from unsigned char*

        if(header.magicNumber == "P5") {
            size_t idx = 0;
            if (header.numChannels != 1) {
                std::cerr << "Error: P5 format requires 1 channel" << std::endl;
                delete[] buffer;
                file.close();
                return;
            }
            for (int y = 0; y < header.height; ++y) {
                for (int x = 0; x < header.width; ++x) {
                    std::vector<T> pixel = image.getPixel(x, y);  // Changed to vector<T>
                    if (pixel.size() != 1) {
                        std::cerr << "Error: Invalid pixel data at (" << x << "," << y << ")" << std::endl;
                        delete[] buffer;
                        file.close();
                        return;
                    }
                    buffer[idx++] = pixel[0];
                }
            }
        } 
        else if(header.magicNumber == "P6") {
            size_t idx = 0;
            if (header.numChannels != 3) {
                std::cerr << "Error: P6 format requires 3 channels" << std::endl;
                delete[] buffer;
                file.close();
                return;
            }
            for (int y = 0; y < header.height; ++y) {
                for (int x = 0; x < header.width; ++x) {
                    std::vector<T> pixel = image.getPixel(x, y);  // Changed to vector<T>
                    if (pixel.size() != 3) {
                        std::cerr << "Error: Invalid pixel data at (" << x << "," << y << ")" << std::endl;
                        delete[] buffer;
                        file.close();
                        return;
                    }
                    buffer[idx++] = pixel[0];
                    buffer[idx++] = pixel[1];
                    buffer[idx++] = pixel[2];
                }
            }
        } else {
            std::cerr << "Error: Invalid magic number " << header.magicNumber << std::endl;
            delete[] buffer;
            file.close();
            return;
        }

        // Write exactly bufferSize bytes
        file.write(reinterpret_cast<const char*>(buffer), bufferSize * sizeof(T));  // Added sizeof(T)
        delete[] buffer;
        file.close();
    }
};

#endif // IMAGEIO_H