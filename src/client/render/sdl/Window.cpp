#include "Window.h"

#include "../../ClientOptions.h"
#include "../Render.h"
#include "../Sprite.h"
#include "SDLErrors.h"

namespace Client {

Window::Window() : m_textureManager{},
m_mainWindow{nullptr}, m_renderer{nullptr},
m_screenTexture{nullptr}, m_screenPixels{} {
    if (init() != WindowStatus::GOOD) {
        exit(1);
    }
}

Window::~Window() {
    SDL_DestroyTexture(m_screenTexture);
    m_screenTexture = nullptr;
    
    SDL_DestroyRenderer(m_renderer);
    m_renderer = nullptr;
    
    SDL_DestroyWindow(m_mainWindow);
    m_mainWindow = nullptr;
    
    SDL_Quit();
}

WindowStatus Window::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDLError(SDLErrorMsg::INIT);
        return WindowStatus::FAILED;
    }
    SDL_SetRelativeMouseMode(SDL_TRUE);
    
    m_screenPixels.resize(WINDOW_WIDTH *
                          WINDOW_HEIGHT);

    m_mainWindow = SDL_CreateWindow(
        "OODM",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (m_mainWindow == nullptr) {
        SDLError(SDLErrorMsg::WINDOW_INIT);
        return WindowStatus::FAILED;
    }
    
    m_renderer = SDL_CreateRenderer
        (m_mainWindow, -1, SDL_RENDERER_ACCELERATED);
    if (m_renderer == nullptr) {
        SDLError(SDLErrorMsg::RENDERER_INIT);
        return WindowStatus::FAILED;
    }
    SDL_SetRenderDrawColor(m_renderer, 0, 0,
                           0, 0xff);
    
    m_screenTexture =
    SDL_CreateTexture(m_renderer,
                      SDL_PIXELFORMAT_ABGR8888,
                      SDL_TEXTUREACCESS_STREAMING,
                      WINDOW_WIDTH,
                      WINDOW_HEIGHT);

    return WindowStatus::GOOD;
}

void Window::draw(const GameState& gameState) {
    std::vector<Sprite> sprites{
        {13, 13, 30},
        {3, 3, 29}
    };
    render(gameState, m_screenPixels, m_textureManager, sprites);
    
    SDL_UpdateTexture(m_screenTexture,
                        nullptr,
                        reinterpret_cast<void*>(m_screenPixels.data()),
                        WINDOW_WIDTH * 4);
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_screenTexture,
                   nullptr, nullptr);
    SDL_RenderPresent(m_renderer);
    SDL_Delay(10);
}

}
