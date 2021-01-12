///////////////////////////////////////////////////////////////////////////////
//  File    :   types.h
//  Brief   :   Bridges types represent the HTTP domain model
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#ifndef BRIDGES_TYPES_H
#define BRIDGES_TYPES_H

#include <bridges/defs.h>

namespace bridges 
{
#define SET_BIT(i) 0x1 << i

class Request;
class Response;
class Headers;
class Socket;

using String    = std::string;
using Path      = String;
using Buffer    = String;
using URI       = String;
using Tokens    = std::vector<String>;
using Handler   = std::function<void(const Request&, Response&)>;

// TODO: Consider making a method class that encapsulates string conversion, 
// and scopes the type to only these valid enumerations. I.E. the type system does 
// not ensure a Method is one of these enums currently.
using Method    =   uint16_t;
enum
{
INVALID         =   SET_BIT(0),
GET             =   SET_BIT(1),
HEAD            =   SET_BIT(2),
POST            =   SET_BIT(3),
PUT             =   SET_BIT(4),
DELETE          =   SET_BIT(5),
CONNECT         =   SET_BIT(6),
OPTIONS         =   SET_BIT(7),
TRACE           =   SET_BIT(8),
PATCH           =   SET_BIT(9)
};

struct Request_Handler {
    const char* route;
    Handler action;
};
using Handler_Table  = std::map<Method, std::vector<Request_Handler>>;

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


} // namespace bridges

#endif // BRIDGES_TYPES_H
