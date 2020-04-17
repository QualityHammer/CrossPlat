#include "GameMap.hpp"

namespace Common {

const u8& GameMap::operator[](const u16 index) const {
    return data[index];
}

}
