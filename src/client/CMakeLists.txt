set (render_hpp
    render/Image.hpp
    render/Sprite.hpp
    render/Pixels.hpp
    render/Render.hpp
)

set (render
    render/Image.cpp
    render/Render.cpp
)

set (input_hpp
    input/MouseState.hpp
    input/KeyboardState.hpp
)

set (input
    input/InputManager.cpp
    input/MouseState.cpp
    input/KeyboardState.cpp
)

set (sdl_hpp
    render/sdl/SDLErrors.hpp
    render/sdl/Window.hpp
)

set (sdl
    render/sdl/SDLErrors.cpp
    render/sdl/Window.cpp
)

set (texture_hpp
    render/texture/TextureManager.hpp
    render/texture/Texture.hpp
    render/texture/TextureErrors.hpp
)

set (texture
    render/texture/TextureManager.cpp
    render/texture/Texture.cpp
    render/texture/TextureErrors.cpp
)

set (network_hpp
    network/ClientNet.hpp
)

set (network
    network/ClientNet.cpp
)

set (utils_hpp
    utils/FrameTimer.hpp
)

set (utils
    utils/FrameTimer.cpp
)

add_library(cplat_client
	Client.cpp
    GameState.cpp
    ${render}
    ${sdl}
    ${texture}
    ${input}
    ${network}
    ${utils}

    Client.hpp
    ClientOptions.hpp
    GameState.hpp
    ${render_hpp}
    ${sdl_hpp}
    ${texture_hpp}
    ${input_hpp}
    ${network_hpp}
    ${utils_hpp}
)

set_compiler_flags(cplat_client)

# Set folder structure for IDEs
#   DIRECTORY
#--------------
#   render/
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/"
            PREFIX "Header Files" FILES ${render_hpp})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/"
            PREFIX "Source Files" FILES ${render})
#   render/sdl/
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/"
            PREFIX "Header Files" FILES ${sdl_hpp})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/"
            PREFIX "Source Files" FILES ${sdl})
#   render/texture/
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/"
            PREFIX "Header Files" FILES ${texture_hpp})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/"
            PREFIX "Source Files" FILES ${texture})
#   input/
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/"
            PREFIX "Header Files" FILES ${input_hpp})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/"
            PREFIX "Source Files" FILES ${input})
#   network/
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/"
            PREFIX "Header Files" FILES ${network_hpp})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/"
            PREFIX "Source Files" FILES ${network})
#   utils/
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/"
            PREFIX "Header Files" FILES ${utils_cpp})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/"
            PREFIX "Source Files" FILES ${utils})

target_include_directories(cplat_client
    PRIVATE
    "${CMAKE_SOURCE_DIR}/dependencies"
    "${CMAKE_SOURCE_DIR}/src/server"
    "${CMAKE_SOURCE_DIR}/src/common"
)

target_include_directories(cplat_client
    PUBLIC
    ${SDL2_INCLUDE_DIR}
)

target_link_libraries(cplat_client
	cplat_common
	cplat_server
	${SDL2_LIBRARY}
)
