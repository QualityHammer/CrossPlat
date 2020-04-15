add_library(cplat_server
	Server.cpp
 
    Server.hpp
)

set_compiler_flags(cplat_server)

target_include_directories(cplat_server
    PRIVATE
    "${CMAKE_SOURCE_DIR}/src/common"
)

target_link_libraries(cplat_server
	cplat_common
)
