add_library(cplat_common
	Common.cpp
	ErrorHandler.cpp
 
    Common.h
    ErrorHandler.h
    Types.h
)

set_compiler_flags(cplat_common)
set_property(TARGET cplat_common PROPERTY FOLDER "Common")
