#include "SDLErrors.h"

#include <SDL.h>
#include <iostream>

extern void SDLError(const SDLErrorMsg msg) {
    std::cout << errorMsgStrings[static_cast<u8>(msg)]
        << " SDL Error:" << std::endl
        << SDL_GetError() << std::endl;
}
