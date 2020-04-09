add_library(cplat_common
	Common.cpp
	ErrorHandler.cpp
    GameMap.cpp
 
    Common.h
    ErrorHandler.h
    Types.h
    PlayerControl.h
    GameMap.h
)

set_compiler_flags(cplat_common)
