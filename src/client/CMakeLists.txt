add_library(cplat_client
	Client.cpp
	SDLErrors.cpp
	Window.cpp
)

set_compiler_flags(cplat_client)
set_property(TARGET cplat_client PROPERTY FOLDER "Client")

target_link_libraries(cplat_client
	cplat_common
	cplat_server
	${SDL2_LIBRARY}
)