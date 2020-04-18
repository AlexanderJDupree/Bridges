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

#endif // BRIDGES_DEFS_H
