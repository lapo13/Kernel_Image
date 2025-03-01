#include <string>
#include <Image.h>

template <typename PixelType, unsigned int NumChannels>
class ImageIO {
public:
    static void saveImage(const std::string& filename, const Image& image);
    static Image loadImage(const std::string& filename);
};