cmake_minimum_required(VERSION 3.2)
project(bridges_tests)

set(TEST_BIN ${BRIDGES_BIN}/tests)

include_directories(${BRIDGES_INCLUDE})
include_directories(../third_party/googletest/googletest/include)

set( SOURCE_FILES 
    run_tests.cpp
    defs_tests.cpp
    ../src/server.cpp
    server_tests.cpp
   )

add_executable(bridges_tests ${SOURCE_FILES})
target_link_libraries(bridges_tests gtest)
install(TARGETS bridges_tests DESTINATION ${TEST_BIN})