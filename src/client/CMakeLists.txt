add_library(cplat_client
	Client.cpp
	SDLErrors.cpp
	Window.cpp
	Image.cpp
    Render.cpp
    GameState.cpp
 
    Client.h
    SDLErrors.h
    Window.h
    Image.h
    ClientOptions.h
    RenderTypes.h
    Render.h
    GameState.h
)

set_compiler_flags(cplat_client)
set_property(TARGET cplat_client PROPERTY FOLDER "Client")

target_link_libraries(cplat_client
	cplat_common
	cplat_server
    utils
	${SDL2_LIBRARY}
)
