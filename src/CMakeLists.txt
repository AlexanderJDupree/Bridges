cmake_minimum_required(VERSION 3.2)
project(bridges)


add_library(bridges STATIC 
            server.cpp
            socket.cpp
            common.cpp
           )

add_executable(Bridges 
               main.cpp
              )

target_link_libraries(Bridges bridges)

install(TARGETS Bridges DESTINATION ${BRIDGES_BIN})
install(TARGETS bridges DESTINATION lib)