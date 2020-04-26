///////////////////////////////////////////////////////////////////////////////
//  File    :   server.cpp
//  Brief   :   Bridges http server implementation
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#include <bridges/socket.h>

namespace bridges
{

Socket::Socket
    (
    socket_t    socket,
    size_t      read_timeout_sec,
    size_t      read_timeout_usec
    )
: _socket               ( socket            )
, _read_timeout_sec     ( read_timeout_sec  )
, _read_timeout_usec    ( read_timeout_usec )
{
}

}