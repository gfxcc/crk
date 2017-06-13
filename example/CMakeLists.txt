#
# author: <gfxcc_stevens@outlook.com>
# created: 2017-06-07

cmake_minimum_required(VERSION 2.8.11)

# In-source builds are disabled.
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR
        "CMake generation is not possible within the source directory!"
        "\n Remove the CMakeCache.txt file and try again from another folder, e.g.:"
        "\n "
        "\n rm CMakeCache.txt"
        "\n mkdir build"
        "\n cd build"
        "\n cmake .."
    )
endif()


PROJECT(sample)
MESSAGE(STATUS "Project: ${PROJECT_NAME}")
file(GLOB_RECURSE header ${sample_SOURCE_DIR}/*.h)
file(GLOB_RECURSE source ${sample_SOURCE_DIR}/*.cc)
#list(REMOVE_ITEM source ${iShare_SOURCE_DIR}/MMGAPN/feedback.cpp ${iShare_SOURCE_DIR}/MMGAPN/main.cpp)
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS "-std=c++11")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

include_directories(
	${sample_SOURCE_DIR}/../include/
	)

link_directories(${sample_SOURCE_DIR}/../lib/)

add_executable(sample ${source})

target_link_libraries(sample
	crk
	)
