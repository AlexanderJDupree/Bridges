cmake_minimum_required(VERSION 3.2)
project(bridges)

set(SOURCE_FILES 
    main.cpp
    server.cpp
    )

add_executable(bridges ${SOURCE_FILES})
install(TARGETS bridges DESTINATION ${BRIDGES_BIN})