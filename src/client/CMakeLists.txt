set (render_h
    render/Image.h
    render/Sprite.h
    render/Player.h
    render/Pixels.h
    render/Render.h
)

set (render
    render/Image.cpp
    render/Render.cpp
)

set (input_h
    input/MouseState.h
    input/KeyboardState.h
)

set (input
    input/InputManager.cpp
    input/MouseState.cpp
    input/KeyboardState.cpp
)

set (sdl_h
    render/sdl/SDLErrors.h
    render/sdl/Window.h
)

set (sdl
    render/sdl/SDLErrors.cpp
    render/sdl/Window.cpp
)

set (texture_h
    render/texture/TextureManager.h
    render/texture/Texture.h
    render/texture/TextureErrors.h
)

set (texture
    render/texture/TextureManager.cpp
    render/texture/Texture.cpp
    render/texture/TextureErrors.cpp
)

add_library(cplat_client
	Client.cpp
    GameState.cpp
    ${render}
    ${sdl}
    ${texture}
    ${input}
 
    Client.h
    ClientOptions.h
    GameState.h
    ${render_h}
    ${sdl_h}
    ${texture_h}
    ${input_h}
)

set_compiler_flags(cplat_client)

# Set folder structure for IDEs
#   DIRECTORY
#--------------
#   render/
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/"
            PREFIX "Header Files" FILES ${render_h})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/"
            PREFIX "Source Files" FILES ${render})
#   render/sdl/
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/"
            PREFIX "Header Files" FILES ${sdl_h})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/"
            PREFIX "Source Files" FILES ${sdl})
#   render/texture/
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/"
            PREFIX "Header Files" FILES ${texture_h})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/"
            PREFIX "Source Files" FILES ${texture})
#   input/
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/"
            PREFIX "Header Files" FILES ${input_h})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/"
            PREFIX "Source Files" FILES ${input})


target_link_libraries(cplat_client
	cplat_common
	cplat_server
    enet
	${SDL2_LIBRARY}
)
