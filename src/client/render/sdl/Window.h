#pragma once

#include <SDL.h>

#include <common/Types.h>
#include "../../GameState.h"
#include "../texture/TextureManager.h"

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
    TextureManager m_textureManager;

    SDL_Window* m_mainWindow;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_screenTexture;
    Pixels m_screenPixels;
    
    WindowStatus init();
};

}
