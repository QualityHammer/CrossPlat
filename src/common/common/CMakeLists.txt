set (constructs_h
    constructs/Types.h
    constructs/PlayerControl.h
    constructs/GameMap.h
    constructs/Entity.h
)

set (constructs
    constructs/GameMap.cpp
)

add_library(cplat_common
	ErrorHandler.cpp
    ${constructs}
 
    ErrorHandler.h
    ${constructs_h}
)

set_compiler_flags(cplat_common)

# Set folder structure for IDEs
#   DIRECTORY
#--------------
#   constructs/
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/"
            PREFIX "Header Files" FILES ${constructs_h})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/"
            PREFIX "Source Files" FILES ${constructs})

target_link_libraries(cplat_common
    enet
)
