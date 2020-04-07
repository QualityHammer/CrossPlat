#include "client/Window.h"

#include <SDL.h>
#undef main

int main() {
	Client::Window window{};
  SDL_Event e;
  bool quit{false};
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
        case SDL_QUIT:
          quit = true;
          break;
      }
    }
  }
	return 0;
}
