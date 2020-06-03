cmake_minimum_required(VERSION 3.2)
project(bridges_tests)

include_directories(${BRIDGES_INCLUDE})
include_directories(${THIRD_PARTY_INCLUDE}/googletest/googletest/include)

set( SOURCE_FILES 
    run_tests.cpp
    server_tests.cpp
    socket_tests.cpp
    parser_tests.cpp
   )

add_executable(bridges_tests ${SOURCE_FILES})

target_link_libraries(bridges_tests gtest)
target_link_libraries(bridges_tests bridges)

install(TARGETS bridges_tests DESTINATION ${BRIDGES_BIN})