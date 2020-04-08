#pragma once

#include <SDL.h>

#include "Image.h"
#include "GameState.h"

namespace Client {

enum class WindowStatus {
    GOOD,
    FAILED
};

class Window {
public:
    Window();
    ~Window();
    
    void draw(const GameState& gameState);
private:
    WindowStatus init();

    SDL_Window* m_mainWindow;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_screenTexture;
    Pixels m_screenPixels;
    
    Pixels m_wall;
};

}
