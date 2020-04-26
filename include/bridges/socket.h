
///////////////////////////////////////////////////////////////////////////////
//  File    :   socket_stream.h
//  Brief   :   Defines a stream abstraction for reading data from socket 
//              connections
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#ifndef BRIDGES_SOCKET_H
#define BRIDGES_SOCKET_H

#include <bridges/defs.h>

namespace bridges
{

class Socket
{
public:

    Socket
        (
        socket_t    socket              = INVALID_SOCKET,
        size_t      read_timeout_sec    = DFLT_READ_TIMEOUT_SEC,
        size_t      read_timeout_usec   = DFLT_READ_TIMEOUT_USEC
        );

    operator socket_t() const { return _socket; }

private:

    socket_t    _socket;
    size_t      _read_timeout_sec;
    size_t      _read_timeout_usec;

};

}

#endif  // BRIDGES_SOCKET_STREAM_H