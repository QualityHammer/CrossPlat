#pragma once

#include <string>
#include <vector>

#include <common/Types.h>

namespace Client {

using Color = u32;
using Pixels = std::vector<Color>;

Color packColor(const u8 r, const u8 g,
                const u8 b, const u8 a=255);

}
