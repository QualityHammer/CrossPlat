#include "Image.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <cmath>
#define STB_IMAGE_IMPLEMENTATION
#include <utils/stb_image.h>

#include "ClientOptions.h"
#include <common/ErrorHandler.h>

namespace Client {

Color packColor(const u8 r, const u8 g,
                const u8 b, const u8 a) {
    return (a << 24) + (b << 16) + (g << 8) + r;
}

bool loadTexture(const std::string filename,
                 Pixels& pixels,
                 size_t& textSize,
                 size_t& textCnt) {
    int nchannels{-1}, w, h;
    unsigned char* pixmap{stbi_load(filename.c_str(),
                                    &w, &h,
                                    &nchannels,
                                    0)};
    if (!pixmap) {
        Error(ErrorMsg::TEXTURE_LOAD);
        return false;
    }
    
    if (nchannels != 4) {
        Error(ErrorMsg::TEXTURE_CHANNELS);
        stbi_image_free(pixmap);
        return false;
    }
    
    textCnt = w / h;
    textSize = w / textCnt;
    if (w != h * (int)textCnt) {
        Error(ErrorMsg::TEXTURE_COUNT);
        stbi_image_free(pixmap);
        return false;
    }
    
    pixels = Pixels{};
    pixels.resize(w * h);
    for (u16 j{0}; j < h; j++) {
        for (u16 i{0}; i < w; i++) {
            u8 r{pixmap[(i + j * w) * 4 + 0]};
            u8 g{pixmap[(i + j * w) * 4 + 1]};
            u8 b{pixmap[(i + j * w) * 4 + 2]};
            u8 a{pixmap[(i + j * w) * 4 + 3]};
            pixels[i + j * w] = packColor(r, g, b, a);
        }
    }
    stbi_image_free(pixmap);
    return true;
}

}
