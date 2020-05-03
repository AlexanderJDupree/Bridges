///////////////////////////////////////////////////////////////////////////////
//  File    :   system.h
//
//  Brief   :   Defines Mock interfaces for Bridges dependencies
//
//  Author  :   Alexander DuPree
//
//  License :   MIT
//
///////////////////////////////////////////////////////////////////////////////

#ifndef BRIDGES_TESTS_MOCKS_H
#define BRIDGES_TESTS_MOCKS_H

#include <bridges/defs.h>

namespace bridges
{

class Mock_System_Interface 
{
public:

    int bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen) {
        return ::bind(sockfd, addr, addrlen);
    }

};

static Mock_System_Interface system;
    
} // namespace bridges

#endif // BRIDGES_TESTS_MOCKS_H