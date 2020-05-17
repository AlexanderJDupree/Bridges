///////////////////////////////////////////////////////////////////////////////
//  File    :   defs.h ( precompiled-header )
//  Brief   :   Common includes and constants defined for the project
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Configuration
///////////////////////////////////////////////////////////////////////////////

#ifndef BRIDGES_DEFS_H
#define BRIDGES_DEFS_H

#define BRIDGES_VERSION_MAJOR 0
#define BRIDGES_VERSION_MINOR 2
#define BRIDGES_VERSION_PATCH 0

#define BRIDGES_VERSION "0.2.0"

#define BRIDGES_HTTP_MAX_LINE_LENGTH  8192
#define BRIDGES_HTTP_MAX_REQUEST_SIZE 65536

#define DFLT_KEEP_ALIVE_MAX 5

#define DFLT_READ_TIMEOUT_SEC 5
#define DFLT_READ_TIMEOUT_USEC 0
#define DFLT_READ_TIMEOUT { DFLT_READ_TIMEOUT_SEC, DFLT_READ_TIMEOUT_USEC }

#define DFLT_SERVER_BACKLOG 5

#define DFLT_DOCUMENT_ROOT  "/var/www"

///////////////////////////////////////////////////////////////////////////////
// General Includes
///////////////////////////////////////////////////////////////////////////////

#include <map>
#include <tuple>
#include <string>
#include <cctype>
#include <vector>
#include <cstdint>
#include <iterator>
#include <optional>
#include <algorithm>
#include <functional>

#include "strtk/strtk.hpp" // TODO: Abstract this dependency behind an API

///////////////////////////////////////////////////////////////////////////////
// Platform Specific Includes & Typedefs
///////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32 

#include <WS2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")

#define SHUT_RD   SD_RECEIVE
#define SHUT_WR	  SD_SEND
#define SHUT_RDWR SD_BOTH

#define WS_VERSION MAKEWORD(2,0)	/* Requested Windows Socket Verion */

#undef DELETE

using ssize_t  = long long;
using socket_t = SOCKET;

#else  // Unix

#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <string.h>

#define INVALID_SOCKET (-1)

using socket_t = int;

#endif  // _WIN32

#endif // BRIDGES_DEFS_H
