cmake_minimum_required(VERSION 3.16)

project(CrossPlat VERSION 1.0
  DESCRIPTION "A silly Wolfenstein-like 'Game' for me to learn stuff."
	LANGUAGES CXX)
include(cmake/ProjectSettings.cmake)

# Interface for c++ std and compile-time options
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

# Enable time-tracing on clang
if (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(ENABLE_BUILD_WITH_TIME_TRACE
    "Enable -ftime-trace to generate time tracing .json files on clang"
    OFF)
  if (ENABLE_BUILD_WITH_TIME_TRACE)
    add_compile_definitions(project_options INTERFACE -ftime-trace)
  endif()
endif()

# Interface for warning settings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

set(
	CMAKE_MODULE_PATH
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake"
	${CMAKE_MODULE_PATH}
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)


function (include_all target)
	target_include_directories(${target}
		PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/dependencies"
		"${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/server"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/common"
	)
endfunction(include_all)

function (link_all target)
	target_link_libraries(${target}
		cplat_client
		cplat_common
		cplat_server
	)
endfunction(link_all)

find_package(SDL2 REQUIRED)

add_subdirectory(dependencies)

add_subdirectory(src/common/common)
add_subdirectory(src/server)
add_subdirectory(src/client)

add_executable(${PROJECT_NAME}
	src/Main.cpp
)

set_compiler_flags(${PROJECT_NAME})
include_all(${PROJECT_NAME})
link_all(${PROJECT_NAME})
