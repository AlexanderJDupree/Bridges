///////////////////////////////////////////////////////////////////////////////
//  File    :   common.h
//  Brief   :   common functions and details 
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#ifndef BRIDGES_COMMON_H
#define BRIDGES_COMMON_H

#include <tuple>

#include <bridges/defs.h>

namespace bridges 
{

struct time_t  {
    size_t sec;
    size_t usec;
};

constexpr inline bool operator==
    (
    const time_t& lhs, 
    const time_t& rhs
    )
{
    return std::tie(lhs.sec, lhs.usec) == std::tie(rhs.sec, lhs.usec);
}

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
