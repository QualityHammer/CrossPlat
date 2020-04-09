#pragma once

#include <vector>

#include <common/Types.h>

namespace Client {

struct Sprite {
    float x;
    float y;
    u8 texID;
};

using Sprites = std::vector<Sprite>;

}
