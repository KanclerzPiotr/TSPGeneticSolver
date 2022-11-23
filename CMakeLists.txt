cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_COMPILER icpx)
# set(CMAKE_BUILD_TYPE RelWithDebInfo)

project(TSPGeneticSolver VERSION 1.0 LANGUAGES CXX)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(SYCL_FLAGS 
        "-fsycl" 
        "-fsycl-targets=nvptx64-nvidia-cuda"
        "-Wno-unknown-cuda-version"
        "-Wno-linker-warnings")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SYCL_FLAGS}")
endif()

set(TARGET TSPSolver)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
add_compile_options(-O0 -g -Wall -Wextra)

add_executable(${TARGET})
add_subdirectory(src)

target_include_directories(${TARGET} PRIVATE ./include)