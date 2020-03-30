cmake_minimum_required(VERSION 3.2)

project(bridges)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3 -Wall -Werror")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(BRIDGES_INCLUDE ${PROJECT_SOURCE_DIR}/include)
set(BRIDGES_BIN ${PROJECT_SOURCE_DIR}/bin)

include_directories(${BRIDGES_INCLUDE})

add_subdirectory(src)
add_subdirectory(tests)
