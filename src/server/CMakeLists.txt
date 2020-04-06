add_library(cplat_server
	Server.cpp
)

set_compiler_flags(cplat_server)

target_link_libraries(cplat_server
	cplat_common
)