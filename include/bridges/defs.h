///////////////////////////////////////////////////////////////////////////////
//  File    :   defs.h
//  Brief   :   Common includes and constants defined for the project
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#ifndef BRIDGES_DEFS_H
#define BRIDGES_DEFS_H

#define BRIDGES_VERSION_MAJOR 0
#define BRIDGES_VERSION_MINOR 1
#define BRIDGES_VERSION_PATCH 0

#define BRIDGES_VERSION "0.1.0"

///////////////////////////////////////////////////////////////////////////////
// General Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <stdint.h>

#ifdef _WIN32 

#include <WS2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")

#define SHUT_RD   SD_RECEIVE
#define SHUT_WR	  SD_SEND
#define SHUT_RDWR SD_BOTH

#else  // Unix

#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <string.h>

#define INVALID_SOCKET (-1)


#endif  // _WIN32

///////////////////////////////////////////////////////////////////////////////
// Common Types
///////////////////////////////////////////////////////////////////////////////

#define clear_struct(x) memset(&x, 0, sizeof(x))

namespace bridges
{
using Method    = uint16_t;
using Path      = std::string;
using Buffer    = std::string;
using Socket    = int;
} // namespace bridges

#endif // BRIDGES_DEFS_H
