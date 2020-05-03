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

// TODO: Reaseach better ways to mock system calls

#include <bridges/defs.h>

namespace bridges
{

class Mock_System_Interface 
{
public:

    struct __bind {
        int operator()(int sockfd, const struct sockaddr* addr, socklen_t addrlen){
            return ::bind(sockfd, addr, addrlen);
        }

    } bind;

};

static Mock_System_Interface system;
    
} // namespace bridges

#endif // BRIDGES_TESTS_MOCKS_H