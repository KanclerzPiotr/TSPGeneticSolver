# cmake_minimum_required(VERSION 3.20)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_COMPILER clang++)
# # set(CMAKE_CXX_COMPILER icpx)
# # set(CMAKE_BUILD_TYPE RelWithDebInfo)

# project(TSPGeneticSolver VERSION 1.0 LANGUAGES CXX)

# if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
#     set(SYCL_FLAGS 
#         "-fsycl" 
#         "-fsycl-targets=nvptx64-nvidia-cuda"
#         "-Wno-unknown-cuda-version"
#         "-Wno-linker-warnings")
# endif()


# # add_compile_options(-O0 -g -Wall -Wextra )


# add_subdirectory(src)

# target_include_directories(${TARGET} PRIVATE ./include)
# target_compile_options(${TARGET} PUBLIC ${SYCL_FLAGS})
# target_link_libraries(${TARGET} PRIVATE -fsycl)

cmake_minimum_required(VERSION 3.0.0)

# set(CMAKE_CXX_COMPILER clang++)

project(TSPGeneticSolver VERSION 0.1.0 LANGUAGES CXX)

set(TARGET TSPSolver)
if(${CMAKE_CXX_COMPILER} MATCHES "clang")
      set(CUDA_FLAGS 
            "-fsycl-targets=nvptx64-nvidia-cuda"
            "-Wno-unknown-cuda-version"
            "-Wno-linker-warnings"
            )
endif()

set (SYCL_FLAGS 
      "${CUDA_FLAGS}"
      "-fsycl"
      "-fsycl-unnamed-lambda"
      "-O3"
      "-g")


add_executable(${TARGET})
add_subdirectory(src)

target_compile_features(${TARGET} PRIVATE cxx_std_17)
target_compile_options(${TARGET} PUBLIC ${SYCL_FLAGS})
target_include_directories(${TARGET} PRIVATE ./include)
target_link_libraries(${TARGET} PUBLIC ${SYCL_FLAGS})