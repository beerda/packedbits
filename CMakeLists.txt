cmake_minimum_required(VERSION 3.18)

project(packedbits
    VERSION 1.0
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main)

FetchContent_Declare(googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG main)

FetchContent_MakeAvailable(
    googletest
    googlebenchmark)

find_package(Boost REQUIRED)

enable_testing()

add_subdirectory(src)
add_subdirectory(apps)
