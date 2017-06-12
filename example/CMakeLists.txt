#
# author: <gfxcc_stevens@outlook.com>
# created: 2017-06-07

PROJECT(sample)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
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
