cmake_minimum_required(VERSION 3.2)

project(bridges)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Werror")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(BRIDGES_INCLUDE ${PROJECT_SOURCE_DIR}/include)
set(BRIDGES_BIN ${PROJECT_SOURCE_DIR}/build/bin)

include_directories(${BRIDGES_INCLUDE})

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(third_party/googletest)
