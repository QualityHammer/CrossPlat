cmake_minimum_required(VERSION 3.16)

project(CrossPlat VERSION 1.0
  DESCRIPTION "A silly Wolfenstein-like 'Game' for me to learn stuff."
	LANGUAGES CXX)
include(cmake/ProjectSettings.cmake)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

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

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# enable doxygen
include(cmake/Doxygen.cmake)
enable_doxygen()

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)
option(ENABLE_TESTING "Enable test builds" ON)

include(cmake/Conan.cmake)
run_conan()

if (ENABLE_TESTING)
  enable_testing()
  message(
    "Building tests. Be sure to check out test/constexpr_tests for constexpr testing"
  )
#add_subdirectory(test)
endif()

if (ENABLE_FUZZING)
  message(
    "Building fuzz tests, using fuzzing sanitizer https://www.llvm.org/docs/LibFuzzer.html"
  )
#add_subdirectory(fuzz_test)
endif()

add_subdirectory(include)
add_subdirectory(src)
