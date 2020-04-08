#include "Image.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#define STD_IMAGE_IMPLEMENTATION
#include <utils/stb_image.h>

#include "ClientOptions.h"

namespace Client {

Color packColor(const u8 r, const u8 g,
                const u8 b, const u8 a) {
    return (a << 24) + (b << 16) + (g << 8) + r;
}

}
