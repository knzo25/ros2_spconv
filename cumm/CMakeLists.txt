cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(cumm)

find_package(ament_cmake_auto REQUIRED)
find_package(CUDA)

if(NOT ${CUDA_FOUND})
  message(WARNING "cuda was not found. the cumm package will not be built.")
  return()
endif()

ament_auto_find_build_dependencies()

option(CUMM_DISABLE_CMAKE_INSTALL "disable cumm install" OFF)
message (STATUS "AWDSAF ${CUMM_DISABLE_CMAKE_INSTALL}")
set(CUMM_INCLUDE_PATH ${${PROJECT_NAME}_SOURCE_DIR}/include PARENT_SCOPE)

add_library(${PROJECT_NAME}_cpu INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME}_cpu ALIAS ${PROJECT_NAME}_cpu)
target_include_directories(
  ${PROJECT_NAME}_cpu
  INTERFACE $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_compile_features(${PROJECT_NAME}_cpu INTERFACE cxx_std_14)

include(GNUInstallDirs)

find_package(CUDAToolkit)
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(${PROJECT_NAME}_cpu INTERFACE OpenMP::OpenMP_CXX)
endif()

if(${CUDAToolkit_FOUND})
  add_library(${PROJECT_NAME} INTERFACE)
  add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

  target_include_directories(
    ${PROJECT_NAME}
    INTERFACE $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>
              $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

  target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_14)

  if(OpenMP_CXX_FOUND)
    target_link_libraries(${PROJECT_NAME} INTERFACE OpenMP::OpenMP_CXX CUDA::cudart)

    if (WIN32)
        target_compile_options(${PROJECT_NAME} INTERFACE $<$<COMPILE_LANGUAGE:CUDA>:--extended-lambda -Xcompiler="/openmp">) 
    else()
        target_compile_options(${PROJECT_NAME} INTERFACE $<$<COMPILE_LANGUAGE:CUDA>:--extended-lambda -Xcompiler="-fopenmp">) 
    endif()

  else()
    target_link_libraries(${PROJECT_NAME} INTERFACE CUDA::cudart)
    target_compile_options(${PROJECT_NAME} INTERFACE $<$<COMPILE_LANGUAGE:CUDA>:--extended-lambda>) 

  endif()
  target_compile_definitions(${PROJECT_NAME} INTERFACE TV_CUDA)
  if (NOT CUMM_DISABLE_CMAKE_INSTALL)
    install( 
      TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_cpu
      EXPORT ${PROJECT_NAME}_Targets
      ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
      LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
      RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
  endif()
else()
  if (NOT CUMM_DISABLE_CMAKE_INSTALL)
    install(
      TARGETS ${PROJECT_NAME}_cpu
      EXPORT ${PROJECT_NAME}_Targets
      ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
      LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
      RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
  endif()

endif()

ament_auto_package()