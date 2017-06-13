#
# author: <gfxcc_stevens@outlook.com>
# created: 2017-06-07

###############################################################################
#
# cmake settings
#
###############################################################################

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


PROJECT ("CRK - Chinese Region Kit")
MESSAGE (STATUS "Project: ${PROJECT_NAME}")
file (GLOB_RECURSE header ${PROJECT_SOURCE_DIR}/include/crk/*.h)
file (GLOB_RECURSE source ${PROJECT_SOURCE_DIR}/src/*.cc )

include_directories(
  /usr/local/include/
  ${PROJECT_SOURCE_DIR}/thirdparty/ltp/include/
  ${PROJECT_SOURCE_DIR}/thirdparty/boost/include/
  ${PROJECT_SOURCE_DIR}/include/
  )


# -----------------------------------------------
# COMPILE FLAG
# -----------------------------------------------
SET (CMAKE_BUILD_TYPE "Debug")
SET (CMAKE_CXX_FLAGS "-std=c++11")
SET (CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -Wall -g -ggdb")
SET (CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
#SET (CMAKE_CXX_COMPILER /usr/bin/clang++)
SET (LIBRARY_OUTPUT_PATH    ${PROJECT_SOURCE_DIR}/lib)

link_directories (${PROJECT_SOURCE_DIR}/thirdparty/ltp/lib/)

# -----------------------------------------------
# STATIC LIBRARY
# -----------------------------------------------
ADD_LIBRARY (crk_static_lib STATIC ${source})
TARGET_LINK_LIBRARIES (crk_static_lib
  segmentor
  boost_regex
  postagger
  )
set_target_properties (crk_static_lib PROPERTIES
    OUTPUT_NAME crk)

# -----------------------------------------------
# SHARED LIBRARY
# -----------------------------------------------
ADD_LIBRARY (crk_shared_lib SHARED ${source})
TARGET_LINK_LIBRARIES (crk_shared_lib
  segmentor
  boost_regex
  postagger
  )
set_target_properties (crk_shared_lib PROPERTIES
    OUTPUT_NAME crk)




