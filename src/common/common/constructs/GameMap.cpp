#include "GameMap.h"

namespace Common {

GameMap::GameMap(const GameMapData& data)
: w{data.w}, h{data.h}, size{data.size},
m_data{data.data} {}

const u8& GameMap::operator[](const size_t index) const {
    return m_data[index];
}

}
