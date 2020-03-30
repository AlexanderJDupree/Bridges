cmake_minimum_required(VERSION 3.2)
project(bridges_tests)

add_subdirectory(../third_party/googletest)

set(TEST_BIN ${BRIDGES_BIN}/tests)

include_directories(${BRIDGES_INCLUDE})
include_directories(lib/googletest/googletest/include)

set(SOURCE_FILES run-tests.cpp)

add_executable(bridges-tests ${SOURCE_FILES})
target_link_libraries(bridges_tests gtest)
install(TARGETS bridges_tests DESTINATION ${TEST_BIN})