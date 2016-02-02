cmake_minimum_required (VERSION 2.6)
set(CMAKE_BUILD_TYPE Debug) 
project(dtam)
cmake_policy(SET CMP0012 NEW)

IF(WIN32)
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od")
ELSE(WIN32)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -ggdb ")

ENDIF(WIN32)

find_package(CUDA REQUIRED)

find_package( OpenCV 3.0 REQUIRED )
  CUDA_INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
  INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})

find_package( Qt5Core REQUIRED)

find_package(Boost COMPONENTS system thread)
  LINK_DIRECTORIES(${Boost_LIBRARY_DIR_DEBUG})

#add_definitions( -D__OPENCV_BUILD=1 )
add_definitions( -DCVAPI_EXPORTS )
#message(STATUS ${OpenCV_CONSIDERED_CONFIGS})

macro (add_sources)
    file (RELATIVE_PATH _relPath "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
    foreach (_src ${ARGN})
        get_filename_component(path ${_src} ABSOLUTE)
        list(APPEND DTAM_SOURCES ${path})
        
    endforeach()
    if (_relPath)
        # propagate SRCS to parent directory
        set (DTAM_SOURCES ${DTAM_SOURCES} PARENT_SCOPE)
    endif()
endmacro(add_sources)



set(BASEPATH "${CMAKE_SOURCE_DIR}")
 

#add_library(GraphicsLib SHARED graphics.cpp) #must be in own library so we can link against it.


add_subdirectory(CostVolume)
add_subdirectory(Track)
add_subdirectory(Optimizer) 
add_subdirectory(DepthmapDenoiseWeightedHuber)
add_subdirectory(utils)
#add_subdirectory(Scheduler)
message(${DTAM_SOURCES})

include_directories("${CMAKE_CURRENT_SOURCE_DIR}" ${CUDA_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

SET(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};-gencode arch=compute_52,code=sm_52;--use_fast_math;--restrict;-lineinfo)

set(CUDA_NVCC_FLAGS_RELEASE ${CUDA_NVCC_FLAGS};-O3)
set(CUDA_NVCC_FLAGS_DEBUG ${CUDA_NVCC_FLAGS};-O0)
set(CUDA_NVCC_FLAGS_RELWITHDEBINFO ${CUDA_NVCC_FLAGS};-O3)

cuda_add_library(OpenDTAM SHARED ${DTAM_SOURCES} graphics.cpp)
target_link_libraries(OpenDTAM opencv_cudaimgproc opencv_cudastereo)

#add_executable (a.out testprog.cpp convertAhandaPovRayToStandard.cpp graphics.cpp)
#target_link_libraries( a.out  OpenDTAM ${OpenCV_LIBS} ${Boost_LIBRARIES} )

