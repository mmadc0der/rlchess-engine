cmake_minimum_required(VERSION 3.15)
project(rlchess_engine LANGUAGES CXX)

# --------------------------------------------------
# Build settings
# --------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build type default to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# --------------------------------------------------
# Fetch pybind11
# --------------------------------------------------
include(FetchContent)
FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG        v2.12.0
)
FetchContent_MakeAvailable(pybind11)

# --------------------------------------------------
# Core library
# --------------------------------------------------
add_library(rlchess STATIC
    src/board.cpp
)

target_include_directories(rlchess PUBLIC include)

target_compile_features(rlchess PUBLIC cxx_std_20)

# --------------------------------------------------
# Python module
# --------------------------------------------------
pybind11_add_module(rlchess_engine MODULE bindings/py_module.cpp)

target_link_libraries(rlchess_engine PRIVATE rlchess)

# Ensure module has no "lib" prefix on non-Windows
set_target_properties(rlchess_engine PROPERTIES
    PREFIX ""
    OUTPUT_NAME "rlchess_engine"
)

# --------------------------------------------------
# Tests (optional)
# --------------------------------------------------
include(CTest)
if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()
