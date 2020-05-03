///////////////////////////////////////////////////////////////////////////////
//  File    :   system.h
//
//  Brief   :   Abstracts all system calls behind an interface. This allows us
//              to mock system calls, if needed, and handle unix/windows 
//              system call differences
//
//  Author  :   Alexander DuPree
//
//  License :   MIT
//
///////////////////////////////////////////////////////////////////////////////

#ifndef BRIDGES_SYSTEM_H
#define BRIDGES_SYSTEM_H


#if defined(BRIDGES_TESTS)
#include <mocks.h>
#else

#include <bridges/defs.h>

namespace bridges
{

class System_Interface 
{
public:

    int bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen) {
        return ::bind( sockfd, addr, addrlen);
    }

};

static System_Interface system;
    
} // namespace bridges

#endif // BRIDGES_TESTS
#endif // BRIDGES_SYSTEM_H