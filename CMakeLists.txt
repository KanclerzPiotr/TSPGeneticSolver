cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)

project(TSPGeneticSolver VERSION 1.0 LANGUAGES CXX)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsycl")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(SYCL_FLAGS 
        "-fsycl" 
        "-fsycl-targets=nvptx64-nvidia-cuda"
        "-Wno-unknown-cuda-version"
        "-Wno-linker-warnings")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SYCL_FLAGS}")
endif()

set(TARGET TSPSolver)

add_compile_options(-Wall -Wextra -Wpedantic -fcoroutines)

add_executable(${TARGET})
add_subdirectory(src)
add_subdirectory(include)

target_include_directories(${TARGET} PRIVATE ./include)