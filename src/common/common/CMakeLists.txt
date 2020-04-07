add_library(cplat_common
	Common.cpp
	ErrorHandler.cpp)

set_compiler_flags(cplat_common)
set_property(TARGET cplat_common PROPERTY FOLDER "Common")
