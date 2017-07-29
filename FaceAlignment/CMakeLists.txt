cmake_minimum_required(VERSION 2.8.4)

SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_C_COMPILER "arm-hisiv300-linux-gcc")
SET(CMAKE_CXX_COMPILER "arm-hisiv300-linux-g++")
SET(CMAKE_FIND_ROOT_PATH  "/opt/hisi-linux/x86-arm/arm-hisiv300-linux")

project(seeta_fa_lib)

# Build options
option(BUILD_EXAMPLES  "Set to ON to build examples"  OFF)
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
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
message(STATUS "C++11 support has been enabled by default.")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mcpu=cortex-a7 -mfloat-abi=softfp -mfpu=neon-vfpv4 -mno-unaligned-access -fno-aggressive-loop-optimizations")

include_directories(include)

set(src_files 
    src/cfan.cpp
    src/face_alignment.cpp
    src/sift.cpp
    )

add_library(seeta_fa_lib SHARED ${src_files})
#add_library(seeta_fa_lib STATIC ${src_files})
set(fa_required_libs seeta_fa_lib seeta_facedet_lib)

if (BUILD_EXAMPLES)
    message(STATUS "Build with examples.")
    find_package(OpenCV)
    if (NOT OpenCV_FOUND)
        message(WARNING "OpenCV not found. Test will not be built.")
    else()
        include_directories(${OpenCV_INCLUDE_DIRS} build ../FaceDetection/include)
	link_directories(build)
        list(APPEND fa_required_libs ${OpenCV_LIBS})
        add_executable(fa_test src/test/face_alignment_test.cpp)
        target_link_libraries(fa_test ${fa_required_libs})
    endif()
endif()
