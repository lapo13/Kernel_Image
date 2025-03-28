#ifndef IMAGEIO_H
#define IMAGEIO_H
#include <string>
#include "core/Image.h"
#include "ImageHeader.h"

template<typename T>
class ImageIO {
private:
    ImageIO() = delete;

public:
    static Image<T>* loadImage(const std::string& filename);
    static void saveImage(const std::string &filename, Image<T>& image);
};

#endif // IMAGEIO_H