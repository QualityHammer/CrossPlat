#pragma once

#include <array>
#include <string>

#include <common/constructs/Types.h>

enum class SDLErrorMsg : u8 {
	INIT,
	WINDOW_INIT,
    RENDERER_INIT,
	MSG_COUNT
};

using SDLErrorMsgArray = std::array<std::string,
	static_cast<u8>(SDLErrorMsg::MSG_COUNT)>;

const SDLErrorMsgArray errorMsgStrings{ {
        "SDL could not initialize!",
        "Window could not be created!",
        "Renderer could not be created!",
} };

extern void SDLError(const SDLErrorMsg msg);

