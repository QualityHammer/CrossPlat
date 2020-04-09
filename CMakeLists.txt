cmake_minimum_required(VERSION 3.8...3.16)

if (${CMAKE_VERSION} VERSION_LESS 3.12)
	cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(CrossPlat VERSION 1.0
	DESCRIPTION "A project to learn how to build for all systems."
	LANGUAGES CXX)

set(
	CMAKE_MODULE_PATH
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules"
	${CMAKE_MODULE_PATH}
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

function (set_compiler_flags target)
	target_compile_features(${target}
		PUBLIC
		cxx_std_17
	)

	set_target_properties(${target}
		PROPERTIES
		CXX_EXTENSIONS OFF
	)

	if (MSVC)
		target_compile_options(${target}
			PRIVATE
			/W4
		)
	else()
		target_compile_options(${target}
			PRIVATE
			-Wall
			-Wextra
			-Wshadow
			-Wpointer-arith
			-pedantic
		)
	endif()
endfunction(set_compiler_flags)

function (include_all target)
	target_include_directories(${target}
		PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/dependencies"
		"${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/server"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/common"
		${SDL2_INCLUDE_DIR}
	)
endfunction(include_all)

function (link_all target)
	target_link_libraries(${target}
		cplat_client
		cplat_common
		cplat_server
        enet
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

target_include_directories(cplat_server
	PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/common"
)

target_include_directories(cplat_client
	PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/dependencies"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/server"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/common"
	${SDL2_INCLUDE_DIR}
)

set_compiler_flags(${PROJECT_NAME})
include_all(${PROJECT_NAME})
link_all(${PROJECT_NAME})
