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
    READ,
    WRITE,
    ERROR
};

int poll_socket( socket_t socket, time_t timeout, SELECT_MODE mode);

bool ends_with(const std::string& str, const std::string& suffix);
bool starts_with(const std::string& str, const std::string& prefix);

}
#endif // BRIDGES_COMMON_H
