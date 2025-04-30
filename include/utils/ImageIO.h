#ifndef IMAGEIO_H
#define IMAGEIO_H
#include <string>
#include "core/Image.h"
#include "ImageHeader.h"
#include <fstream>
#include <iostream>
#include <typeinfo>
#include <limits>

namespace ImageIO {

    namespace detail {

        // Helper per controllare apertura file
        inline void checkFileOpen(const std::ios& file, const std::string& filename) {
            if (!file) {
                throw std::runtime_error("Error: Could not open file " + filename);
            }
        }

        // Helper per pulizia buffer
        template<typename T>
        void safeDeleteBuffer(T*& buffer) {
            delete[] buffer;
            buffer = nullptr;
        }

    } // namespace detail

    template<typename T>
    SingleChannelImage<T>* loadGrayImage(const std::string& filename) {
        ImageHeader header;
        std::ifstream file(filename, std::ios::binary);
        detail::checkFileOpen(file, filename);

        // Leggi header
        file >> header.magicNumber;
        if (header.magicNumber != "P5") {
            throw std::runtime_error("Error: File not supported");
        }
        header.numChannels = 1; // PGM ha un solo canale
        file >> header.width >> header.height >> header.maxVal;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Leggi dati immagine
        const size_t bufferSize = header.width * header.height * header.numChannels;
        T* imgBuffer = new T[bufferSize];

        file.read(reinterpret_cast<char*>(imgBuffer), bufferSize * sizeof(T));
        if (file.gcount() != static_cast<std::streamsize>(bufferSize * sizeof(T))) {
            detail::safeDeleteBuffer(imgBuffer);
            throw std::runtime_error("Error: Could not read complete image data");
        }
        file.close();

        // Crea immagine
        Matrix<T>* channel = new Matrix<T>(header.height, header.width);
        size_t idx = 0;
        for (int y = 0; y < header.height; ++y) {
            for (int x = 0; x < header.width; ++x) {
                (*channel)(x, y) = imgBuffer[idx++];
            }
        }
        SingleChannelImage<T>* img = new GrayscaleImage<T>(channel, header);
        detail::safeDeleteBuffer(imgBuffer);
        return img;
    }

    template<typename T>
    MultiChannelImage<T>* loadRGBImage(const std::string& filename) {
        ImageHeader header;
        std::ifstream file(filename, std::ios::binary);
        detail::checkFileOpen(file, filename);

        // Leggi header
        file >> header.magicNumber;
        if (header.magicNumber != "P6") {
            throw std::runtime_error("Error: File not supported");
        }
        header.numChannels = 3; // PPM ha tre canali
        file >> header.width >> header.height >> header.maxVal;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

         // Leggi dati immagine
        const size_t bufferSize = header.width * header.height * header.numChannels;
        T* imgBuffer = new T[bufferSize];
        file.read(reinterpret_cast<char*>(imgBuffer), bufferSize * sizeof(T));
        if (file.gcount() != static_cast<std::streamsize>(bufferSize * sizeof(T))) {
            detail::safeDeleteBuffer(imgBuffer);
            throw std::runtime_error("Error: Could not read complete image data");
            file.close();
        }

        // Crea immagine
        std::vector<Matrix<T>*> channels(header.numChannels);
        for (int i = 0; i < header.numChannels; ++i) {
            channels[i] = new Matrix<T>(header.height, header.width);
        }
        size_t idx;
        for (int c = 0; c < header.numChannels; ++c) {
            idx = c;
            for (int y = 0; y < header.height; ++y) {
                for (int x = 0; x < header.width; ++x) {
                    (*channels[c])(x, y) = imgBuffer[idx];
                    idx += header.numChannels;
                }
            }
        }
        for (int y = 0; y < header.height; ++y) {
            for (int x = 0; x < header.width; ++x) {
                
            }
        }
        MultiChannelImage<T>* img = new ImageRGB<T>(channels, header);
        detail::safeDeleteBuffer(imgBuffer);
        return img;
    }


    template<typename T>
    void saveImage(const std::string& filename, MultiChannelImage<T>& image) {
        std::ofstream file(filename, std::ios::binary);
        detail::checkFileOpen(file, filename);

        ImageHeader header = image.getHeader();
        file << header.magicNumber << "\n";
        file << header.width << " " << header.height << "\n";
        file << header.maxVal << "\n";

        const size_t bufferSize = header.width * header.height * header.numChannels;
        T* buffer = new T[bufferSize];

        size_t idx = 0;
        for (int y = 0; y < header.height; ++y) {
            for (int x = 0; x < header.width; ++x) {
                std::vector<T> pixel = image.getPixel(x, y);
                for (int c = 0; c < header.numChannels; ++c) {
                    if (idx < bufferSize && c < static_cast<int>(pixel.size()))
                        buffer[idx++] = pixel[c];
                }
            }
        }

        file.write(reinterpret_cast<const char*>(buffer), bufferSize * sizeof(T));
        detail::safeDeleteBuffer(buffer);
        file.close();
    }

    template<typename T>
    void saveImage(const std::string& filename, SingleChannelImage<T>& image) {
        std::ofstream file(filename, std::ios::binary);
        detail::checkFileOpen(file, filename);
        ImageHeader header = image.getHeader();
        file << header.magicNumber << "\n";
        file << header.width << " " << header.height << "\n";
        file << header.maxVal << "\n";
        const size_t bufferSize = header.width * header.height * header.numChannels;
        T* buffer = new T[bufferSize];
        size_t idx = 0;
        for (int y = 0; y < header.height; ++y) {
            for (int x = 0; x < header.width; ++x) {
                buffer[idx++] = image.getPixel(x, y);
            }
        }
        file.write(reinterpret_cast<const char*>(buffer), bufferSize * sizeof(T));
        detail::safeDeleteBuffer(buffer);
        file.close();
    }

} 

#endif // IMAGEIO_H