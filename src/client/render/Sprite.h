#pragma once

#include <vector>

#include <common/constructs/Types.h>

namespace Client {

struct Sprite {
    float x;
    float y;
    u8 texID;
};

using Sprites = std::vector<Sprite>;

}
