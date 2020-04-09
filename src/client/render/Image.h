#pragma once

#include <string>
#include <vector>

#include "Pixels.h"
#include <common/Types.h>

namespace Client {

Color packColor(const u8 r, const u8 g,
                const u8 b, const u8 a=255);

bool loadTexture(const std::string filename,
                 Pixels& pixels,
                 size_t& textSize,
                 size_t& textCnt);

}
