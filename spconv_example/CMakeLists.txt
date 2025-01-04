cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(spconv_example LANGUAGES CXX CUDA)

find_package(ament_cmake_auto REQUIRED)
find_package(CUDA)
find_package(CUDAToolkit)

if(NOT ${CUDA_FOUND})
  message(WARNING "cuda was not found. the spconv_example package will not be built.")
  return()
endif()

set(CUMM_DISABLE_CMAKE_INSTALL ON CACHE BOOL "enable X functionality" FORCE)
set(CMAKE_CUDA_ARCHITECTURES 75 86)

add_definitions("-DTV_CUDA --extended-lambda")

ament_auto_find_build_dependencies()

include_directories(
    include
    SYSTEM
    ${spconvlib_INCLUDE_DIRS}
)

add_executable(main main.cu)
target_link_libraries(main ${spconvlib_TARGETS})

ament_auto_package()

