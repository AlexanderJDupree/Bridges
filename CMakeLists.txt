cmake_minimum_required(VERSION 3.2)

project(bridges)

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Werror")
endif()

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(BRIDGES_INCLUDE ${PROJECT_SOURCE_DIR}/include)
set(BRIDGES_BIN ${PROJECT_SOURCE_DIR}/build/bin)

include_directories(${BRIDGES_INCLUDE})

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(third_party/googletest)
