#pragma once

#include <vector>

#include "Types.hpp"

namespace Common {

struct Entity {
    float x;
    float y;
    u8 type;
    u8 texID;
};

using Entities = std::vector<Entity>;

}
