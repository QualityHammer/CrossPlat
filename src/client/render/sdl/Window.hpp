#pragma once

#include <SDL.h>

#include <common/constructs/Types.hpp>
#include "../../GameState.hpp"
#include "../texture/TextureManager.hpp"

namespace Client {

// Status of SDL window.
enum class WindowStatus {
    GOOD,
    FAILED
};

// Representation of an SDL window.
class Window {
public:
    // Initializes window
    Window();
    // Destroys window
    ~Window();
    
    // Draws to the screen according to the
    // current game state.
    void draw(const GameState& gameState);
    
    void setMouseFocus(const bool isFocused) const;
private:
    // Manager for all game textures
    TextureManager m_textureManager;

    // Main SDL window
    SDL_Window* m_mainWindow;
    // SDL renderer
    SDL_Renderer* m_renderer;
    // Main SDL screen texture
    // Fills the whole window
    SDL_Texture* m_screenTexture;
    // All of the pixels used to fill the screen texture.
    Pixels m_screenPixels;
    
    WindowStatus init();
};

}
