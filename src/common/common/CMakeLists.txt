set (constructs_hpp
    constructs/Types.hpp
    constructs/PlayerControl.hpp
    constructs/GameMap.hpp
    constructs/Entity.hpp
)

set (constructs
    constructs/GameMap.cpp
)

add_library(cplat_common
	ErrorHandler.cpp
    ${constructs}
 
    ErrorHandler.hpp
    ${constructs_hpp}
)

set_compiler_flags(cplat_common)

# Set folder structure for IDEs
#   DIRECTORY
#--------------
#   constructs/
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/"
            PREFIX "Header Files" FILES ${constructs_hpp})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/"
            PREFIX "Source Files" FILES ${constructs})

target_link_libraries(cplat_common
    enet
)
