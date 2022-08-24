project(helloworld)
cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions(-DOWT_DEBUG)
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")

include_directories(
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

link_directories(
  "${CMAKE_CURRENT_SOURCE_DIR}/lib"
)

add_executable(helloworld
  main.cpp
)

target_link_libraries(helloworld
  debug -lowt-debug
  optimized -lowt-release
  general sioclient
)
