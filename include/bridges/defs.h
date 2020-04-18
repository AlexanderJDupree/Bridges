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

#ifdef _WIN32 

// TODO add windows support

#else  // Unix

#include <sys/types.h>
#include <sys/socket.h>

#define INVALID_SOCKET (-1)
using socket_t = int;

#endif  // _WIN32

using Method = u_int16_t;

#define GET     0x1 << 0;
#define HEAD    0x1 << 1;
#define POST    0x1 << 2;
#define PUT     0x1 << 3;
#define DELETE  0x1 << 4;
#define CONNECT 0x1 << 5;
#define OPTIONS 0x1 << 6;
#define TRACE   0x1 << 7;
#define PATCH   0x1 << 8;

#endif // BRIDGES_DEFS_H
