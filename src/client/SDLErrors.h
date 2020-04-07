#pragma once

#include <array>
#include <string>

#include <common/Types.h>

enum class SDLErrorMsg : u8 {
	INIT,
	WINDOW_INIT,
	MSG_COUNT
};

using SDLErrorMsgArray = std::array<std::string,
	static_cast<u8>(SDLErrorMsg::MSG_COUNT)>;

namespace SDLErrorHandler {
	void SDLError(const SDLErrorMsg msg);

	const SDLErrorMsgArray errorMsgStrings{ {
			"SDL could not initialize!",
			"Window could not be created!",
	} };
};
