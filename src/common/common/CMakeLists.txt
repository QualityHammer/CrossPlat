add_library(cplat_common
	ErrorHandler.cpp
    GameMap.cpp
 
    ErrorHandler.h
    Types.h
    PlayerControl.h
    GameMap.h
)

set_compiler_flags(cplat_common)
