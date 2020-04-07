#pragma once

#include <SDL.h>

namespace Client {
	enum class WindowStatus {
		GOOD,
		FAILED
	};

	class Window {
	public:
		Window();
		~Window();
	private:
		WindowStatus init();

		SDL_Window* m_mainWindow;
	};
}
