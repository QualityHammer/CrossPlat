#pragma once

#include <array>
#include <string>

#include "constructs/Types.hpp"

// Error types
enum class ErrorMsg : u32 {
    TEXTURE_LOAD,
    TEXTURE_CHANNELS,
    TEXTURE_COUNT,
    MSG_COUNT
};

using ErrorMsgStrings = std::array<
std::string, static_cast<u32>(ErrorMsg::MSG_COUNT)>;

// All error messages
const ErrorMsgStrings errorMsgStrings{{
    "Could not load the textures.",
    "The texture must be a 32 bit image.",
    "The texture file must contain N square" \
    " textures packed horizontally.",
}};

// Error callback
extern void Error(const ErrorMsg msg);
