add_library(cplat_common
	ErrorHandler.cpp
    GameMap.cpp
 
    ErrorHandler.h
    Types.h
    PlayerControl.h
    GameMap.h
    Entity.h
)

set_compiler_flags(cplat_common)

target_link_libraries(cplat_common
    enet
)
