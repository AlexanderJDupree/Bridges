cmake_minimum_required(VERSION 3.2)
project(bridges_tests)

include_directories(${BRIDGES_INCLUDE})
include_directories(../third_party/googletest/googletest/include)

add_compile_definitions(BRIDGES_TESTS)

set( SOURCE_FILES 
    run_tests.cpp
    defs_tests.cpp
    server_tests.cpp
    socket_tests.cpp
   )

add_executable(test_bridges ${SOURCE_FILES})

target_link_libraries(test_bridges gtest)
target_link_libraries(test_bridges bridges)

install(TARGETS test_bridges DESTINATION ${BRIDGES_BIN})