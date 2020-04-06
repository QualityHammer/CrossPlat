add_library(cplat_client
	Client.cpp
 )

set_compiler_flags(cplat_client)

target_link_libraries(cplat_client
	cplat_common
	cplat_server
)