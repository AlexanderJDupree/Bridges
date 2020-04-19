///////////////////////////////////////////////////////////////////////////////
//  File    :   main.cpp
//  Brief   :   Entry Point for Bridges HTTP server
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <bridges/server.h>

int main(int argc, char** argv)
{
    using namespace bridges;

    const std::string banner = "////////////////////////////////////////////////////////////////////////////////";

    std::cout << banner << std::endl;
    std::cout << "BRIDGES" << std::endl;
    std::cout << "version\t:\t" << BRIDGES_VERSION << std::endl;
    std::cout << "License\t:\tMIT\n" << std::endl;
    std::cout << "Copyright (c) 2020 Alexander DuPree" << std::endl;
    std::cout << banner << std::endl;

    std::cout << "\nStarting server on localhost:8000" << std::endl;

    Server server;

    server.listen( "localhost", 8000 );
}
