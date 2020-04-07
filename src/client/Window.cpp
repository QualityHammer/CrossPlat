#include "Window.h"

#include "SDLErrors.h"

namespace Client {
	Window::Window() : m_mainWindow{ nullptr }  {
		if (init() != WindowStatus::GOOD) {
			exit(1);
		}
	}

	Window::~Window() {
		SDL_DestroyWindow(m_mainWindow);
		m_mainWindow = nullptr;
		SDL_Quit();
	}

	WindowStatus Window::init() {
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			SDLErrorHandler::SDLError(SDLErrorMsg::INIT);
			return WindowStatus::FAILED;
		}

		m_mainWindow = SDL_CreateWindow(
			"OODM",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			800, 600,
			SDL_WINDOW_SHOWN
		);
		if (m_mainWindow == nullptr) {
			SDLErrorHandler::SDLError(SDLErrorMsg::WINDOW_INIT);
			return WindowStatus::FAILED;
		}

		return WindowStatus::GOOD;
	}
}