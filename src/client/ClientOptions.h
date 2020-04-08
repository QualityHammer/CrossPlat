#pragma once

#include <cmath>

#include <common/Types.h>

namespace Client {

constexpr u16 WINDOW_WIDTH{800};
constexpr u16 WINDOW_HEIGHT{800};

constexpr u8 MAP_WIDTH{16};
constexpr u8 MAP_HEIGHT{16};

constexpr u8 PIXEL_WIDTH{WINDOW_WIDTH / MAP_WIDTH};
constexpr u8 PIXEL_HEIGHT{WINDOW_HEIGHT / MAP_HEIGHT};

constexpr float FOV{M_PI / 2};

}
