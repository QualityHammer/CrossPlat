#pragma once

#include <string>
#include <vector>
#include <common/Types.h>

using MapData = std::string;

namespace Client {

using Color = u32;
using Pixels = std::vector<Color>;

struct Player {
    float x;
    float y;
    float a;
};

}
