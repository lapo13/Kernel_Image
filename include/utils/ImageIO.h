#include <string>
#include <Image.h>


class ImageIO {
private:
    ImageIO() = delete;
public:
    static void saveImage(const std::string& filename, const Image& image);
    static Image* loadImage(const std::string& filename);
};