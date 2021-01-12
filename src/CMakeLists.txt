cmake_minimum_required(VERSION 3.2)
project(bridges)

add_library(bridges STATIC 
            server.cpp
            socket.cpp
            utility.cpp
            request.cpp
            response.cpp
            headers.cpp
           )

add_executable(run_bridges
               main.cpp
              )

target_link_libraries(bridges fmt::fmt)
target_link_libraries(run_bridges bridges)

install(TARGETS bridges DESTINATION lib)
install(TARGETS run_bridges DESTINATION ${BRIDGES_BIN})