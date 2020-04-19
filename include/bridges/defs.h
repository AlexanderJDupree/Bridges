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

#ifdef _WIN32 

// TODO add windows support

#else  // Unix

#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <string.h>

#define INVALID_SOCKET (-1)

#define clear_struct(x) memset(&x, 0, sizeof(x))

#endif  // _WIN32

///////////////////////////////////////////////////////////////////////////////
// Common Types
///////////////////////////////////////////////////////////////////////////////

namespace bridges
{
using Method = u_int16_t;

using Path = std::string;

using Socket = int;


} // namespace bridges

#endif // BRIDGES_DEFS_H
