#pragma once

#include <vector>

#include "Types.hpp"

namespace Common {

struct GameMapData {
    std::vector<u8> data;
    u16 w;
    u16 h;
    size_t size;
};

class GameMap {
public:
    GameMap(const GameMapData& data);
    
    const u16 w;
    const u16 h;
    const size_t size;
    
    const u8& operator[](const size_t index) const;
private:
    const std::vector<u8> m_data;
};

}
