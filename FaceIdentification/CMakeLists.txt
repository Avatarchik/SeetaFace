cmake_minimum_required (VERSION 2.6)

SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_C_COMPILER "arm-hisiv300-linux-gcc")
SET(CMAKE_CXX_COMPILER "arm-hisiv300-linux-g++")
SET(CMAKE_FIND_ROOT_PATH  "/opt/hisi-linux/x86-arm/arm-hisiv300-linux")

project (viplnet)

set (VIPLNET_VERSION_MAJOR 4)
set (VIPLNET_VERSION_MINOR 5)

option(USE_OPENMP      "Set to ON to build use openmp"  ON)

# Use OpenMP
if (USE_OPENMP)
    find_package(OpenMP QUIET)
    if (OPENMP_FOUND)
        message(STATUS "Use OpenMP")
        add_definitions(-DUSE_OPENMP)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    endif()
endif()

# Use C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "C++11 support has been enabled by default.")

set(CMAKE_BUILD_TYPE "Release")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -std=c++11 -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mcpu=cortex-a7 -mfloat-abi=softfp -mfpu=neon-vfpv4 -mno-unaligned-access -fno-aggressive-loop-optimizations")

MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")

if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
 #   set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DGTEST_USE_OWN_TR1_TUPLE=1")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DGTEST_USE_OWN_TR1_TUPLE=1")
endif (CMAKE_SYSTEM_NAME MATCHES "Darwin")

set(VIPLNET_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/../FaceDetection/include ${PROJECT_SOURCE_DIR}/../FaceAlignment/include)
set(VIPLNET_SRC_DIR ${PROJECT_SOURCE_DIR}/src)
# set __VIOL_LOG__ macro
# add_definitions(-D__VIPL_LOG__)

include_directories(${VIPLNET_INCLUDE_DIR})
include_directories(${VIPLNET_SRC_DIR})

add_subdirectory(src)

aux_source_directory(./src SRC_LIST)
aux_source_directory(./tools TOOLS_LIST)
add_library(viplnet SHARED ${SRC_LIST} ${TOOLS_LIST})
set_target_properties(viplnet PROPERTIES 
  VERSION ${VIPLNET_VERSION_MAJOR}.${VIPLNET_VERSION_MINOR} 
  SOVERSION ${VIPLNET_VERSION_MAJOR}.${VIPLNET_VERSION_MINOR}) 
