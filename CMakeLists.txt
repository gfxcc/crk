#
# author: <gfxcc_stevens@outlook.com>
# created: 2017-06-07

PROJECT ("CRK - Chinese Region Kit")
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
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




