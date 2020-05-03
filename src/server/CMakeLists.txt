add_library(cplat_server
	Server.cpp

    Server.hpp
)

target_include_directories(cplat_server
    PRIVATE
    "${CMAKE_SOURCE_DIR}/src/common"
)

target_link_libraries(cplat_server
  PRIVATE
	cplat_common
  project_options
  project_warnings
  CONAN_PKG::docopt.cpp
  CONAN_PKG::fmt
  CONAN_PKG::spdlog
)
