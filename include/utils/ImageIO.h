#ifndef IMAGEIO_H
#define IMAGEIO_H
#include <string>
#include "core/Image.h"


class ImageIO {
private:
    ImageIO() = delete;
public:
    static Image* loadImage(const std::string& filename);
    static void saveImage(const std::string &filename, Image& image);
};

#endif // IMAGEIO_H