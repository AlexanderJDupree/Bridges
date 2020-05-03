///////////////////////////////////////////////////////////////////////////////
//  File    :   common.h
//  Brief   :   common functions and definitions
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

int poll_socket( socket_t socket, time_t timeout, SELECT_MODE mode);

}// namespace bridges
#endif // BRIDGES_COMMON_H