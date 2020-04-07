#include "client/Window.h"

#include <SDL.h>
#undef main

int main() {
	Client::Window window{};
	SDL_Delay(3000);
	return 0;
}