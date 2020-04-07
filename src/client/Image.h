#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <string>
#include <vector>

#include <common/Types.h>

struct Pixel {
    u8 r;
    u8 g;
    u8 b;
    u8 a;

};

using Image = std::vector<Pixel>;

namespace ImagePack {
    namespace Draw {
        void rectangle(Image &img, const size_t img_w, const size_t img_h,
                        const size_t x, const size_t y, const size_t w,
                        const size_t h, const Pixel color);
    }

    const Pixel packColor(const u8 r, const u8 g, const u8 b, const u8 a=255);
    void ppmImageCreate(const std::string filename, const Image &image,
                        const size_t w, const size_t h);

    void generateImage();
}

#endif // IMAGE_H_INCLUDED
