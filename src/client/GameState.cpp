#include "GameState.hpp"

namespace Client {

GameState::GameState() : player{
    3.456,
    13.345,
    5.023
}, gMap{
    Common::GameMapData{
        {
              1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
              1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
              1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
              1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
              1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
              1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
              1,  0,  0,  0,  0,  0, 18, 19, 20,  0,  0,  0,  0,  0,  0,  1,
              1,  0,  0,  0,  0,  0,  0,  0,  0, 27,  0,  0,  0,  0,  0,  1,
              1,  0,  0,  0,  0, 21,  0,  0,  0, 28,  0,  0,  0,  0,  0,  1,
              1,  0,  0,  0,  0, 22,  0,  0,  0, 29,  0, 13, 14, 15, 16,  1,
              1,  0,  0,  0,  0, 23,  0,  0,  0, 17, 12,  0,  0,  0,  0,  1,
              1,  0,  0,  0,  0, 24,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,
              1,  0,  0,  0,  0,  0, 25,  0, 26, 10, 10,  0,  0,  0,  0,  3,
              1,  0,  0,  0,  0,  0,  0,  0,  0, 11, 11,  0,  0,  0,  0,  4,
              1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  5,
              1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  5,  6,  7,  8,  9,  1
        },
        16,
        16,
        16 * 16
    }
} {}
    
}
