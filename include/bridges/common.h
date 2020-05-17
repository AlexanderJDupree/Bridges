///////////////////////////////////////////////////////////////////////////////
//  File    :   common.h
//  Brief   :   common functions and details 
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#ifndef BRIDGES_COMMON_H
#define BRIDGES_COMMON_H

#include <bridges/defs.h>

///////////////////////////////////////////////////////////////////////////////
// Bridges Macros
///////////////////////////////////////////////////////////////////////////////
#define SET_BIT(i) 0x1 << i
#define CLEAR_STRUCT(x) memset(&x, 0, sizeof(x))

/* This is super hacky but I hate the look of std::optional over Maybe <type> */
#define Maybe std::optional
#define Nothing std::nullopt

namespace bridges 
{

///////////////////////////////////////////////////////////////////////////////
// Common Types and Utilities 
///////////////////////////////////////////////////////////////////////////////

class Request;
class Response;

using String    = std::string;
using Path      = String;
using Buffer    = String;
using URI       = String;
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

struct time_t  {
    size_t sec;
    size_t usec;
};

struct Protocol_Version { 
    uint8_t major;
    uint8_t minor;
};

constexpr inline bool operator==
    (
    const time_t& lhs, 
    const time_t& rhs
    )
{
    return std::tie(lhs.sec, lhs.usec) == std::tie(rhs.sec, lhs.usec);
}

constexpr inline bool operator==
    (
    const Protocol_Version& lhs, 
    const Protocol_Version& rhs
    )
{
    return std::tie(lhs.major, lhs.minor) == std::tie(rhs.major, lhs.minor);
}

///////////////////////////////////////////////////////////////////////////////
// Shared Functions
///////////////////////////////////////////////////////////////////////////////

enum class SELECT_MODE {
    READ_FDS,
    WRITE_FDS,
    ERROR_FDS
};

int poll_socket
    ( 
    socket_t socket, 
    time_t timeout, 
    SELECT_MODE mode
    );

// TODO: Move all these parsing funcitons into a seperate file??
bool process_request_line
    (
    const String& line,
    Request& req 
    );

bool process_header
    (
    const String& header,
    Request& req 
    );

bool has_body
    (
    const Request& req
    );

bool has_whitespace
    (
    const String& str
    );

Method read_method
    (
    const String& method
    );

Protocol_Version read_http_version
    (
    const String& version
    );

}
#endif // BRIDGES_COMMON_H
