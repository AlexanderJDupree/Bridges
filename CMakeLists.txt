cmake_minimum_required(VERSION 3.2)

project(bridges)

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /DEBUG")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Werror")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
endif()

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(BRIDGES_INCLUDE ${PROJECT_SOURCE_DIR}/include)
set(BRIDGES_SOURCE ${PROJECT_SOURCE_DIR}/src})
set(BRIDGES_BIN ${PROJECT_SOURCE_DIR}/build/bin)
set(THIRD_PARTY_INCLUDE ${PROJECT_SOURCE_DIR}/third_party)

add_definitions( -Dstrtk_no_tr1_or_boost )

include_directories(${BRIDGES_INCLUDE} ${THIRD_PARTY_INCLUDE})

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(third_party/googletest)
