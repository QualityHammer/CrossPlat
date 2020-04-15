set (constructs_hpp
    constructs/Types.hpp
    constructs/PlayerControl.hpp
    constructs/GameMap.hpp
    constructs/Entity.hpp
)

set (constructs
    constructs/GameMap.cpp
)

set (network_hpp
    network/Net.hpp
)

set (network
    network/Net.cpp
)

add_library(cplat_common
	ErrorHandler.cpp
    ${constructs}
    ${network}
 
    ErrorHandler.hpp
    ${constructs_hpp}
    ${network_hpp}
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
#   network/
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/"
            PREFIX "Header Files" FILES ${network_hpp})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/"
            PREFIX "Source Files" FILES ${network})

target_include_directories(cplat_common
    PRIVATE
    "${CMAKE_SOURCE_DIR}/dependencies/enet/include"
)

target_link_libraries(cplat_common
    enet
)
