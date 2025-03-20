#ifndef IMAGEIO_H
#define IMAGEIO_H
#include <string>
#include "core/Image.h"


class ImageIO {
private:
    ImageIO() = delete;
public:
    static void saveImage(const std::string& filename, const Image& image);
    static Image* loadImage(const std::string& filename);
};

#endif // IMAGEIO_H