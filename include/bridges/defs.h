///////////////////////////////////////////////////////////////////////////////
//  File    :   defs.h
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
#define BRIDGES_VERSION_MINOR 1
#define BRIDGES_VERSION_PATCH 0

#define BRIDGES_VERSION "0.1.0"

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
#include <string>
#include <vector>
#include <cstdint>
#include <optional>
#include <functional>


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

///////////////////////////////////////////////////////////////////////////////
// Common Types & Utilties
///////////////////////////////////////////////////////////////////////////////

#define SET_BIT(i) 0x1 << i
#define CLEAR_STRUCT(x) memset(&x, 0, sizeof(x))

namespace bridges
{

/* This is super hacky but I hate the look of std::optional over Maybe <type> */
#define Maybe std::optional
#define Nothing std::nullopt

class Request;
class Response;

using String    = std::string;
using Path      = String;
using Buffer    = String;
using URI       = String;

struct case_insensitive_compare { 

    bool operator()(const String& lhs, const String& rhs) {
        return std::lexicographical_compare(
            lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), 
            [](char c1, char c2){ return ::tolower(c1) < ::tolower(c2); }
            );
    }

};

using Headers   = std::map<String, String, case_insensitive_compare>;
using Tokens    = std::vector<String>;

using Method                    =   uint16_t;
static constexpr Method INVALID =   SET_BIT(0);
static constexpr Method GET     =   SET_BIT(1);
static constexpr Method HEAD    =   SET_BIT(2);
static constexpr Method POST    =   SET_BIT(3);
static constexpr Method PUT     =   SET_BIT(4);
static constexpr Method DELETE  =   SET_BIT(5);
static constexpr Method CONNECT =   SET_BIT(6);
static constexpr Method OPTIONS =   SET_BIT(7);
static constexpr Method TRACE   =   SET_BIT(8);
static constexpr Method PATCH   =   SET_BIT(9);

struct Protocol_Version { 
    uint8_t major;
    uint8_t minor;
};

} // namespace bridges

#endif // BRIDGES_DEFS_H
