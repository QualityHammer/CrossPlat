set (render_h
    render/SDLErrors.h
    render/Window.h
    render/Image.h
    render/RenderTypes.h
    render/Render.h
)

set (render
    render/SDLErrors.cpp
    render/Window.cpp
    render/Image.cpp
    render/Render.cpp
)

add_library(cplat_client
	Client.cpp
    GameState.cpp
    ${render}
 
    Client.h
    ClientOptions.h
    GameState.h
    ${render_h}
)

set_compiler_flags(cplat_client)

# Set folder structure for IDEs
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/"
            PREFIX "Header Files" FILES ${render_h})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/"
            PREFIX "Source Files" FILES ${render})

target_link_libraries(cplat_client
	cplat_common
	cplat_server
	${SDL2_LIBRARY}
)
