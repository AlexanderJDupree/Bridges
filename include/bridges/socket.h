///////////////////////////////////////////////////////////////////////////////
//  File    :   socket_stream.h
//  Brief   :   Defines a stream abstraction for reading data from socket 
//              connections
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#ifndef BRIDGES_SOCKET_H
#define BRIDGES_SOCKET_H

#include <functional>

#include <bridges/common.h>

namespace bridges
{

class Socket
{
public:

    Socket
        (
        socket_t    socket          = INVALID_SOCKET,
        time_t      read_timeout    = DFLT_READ_TIMEOUT
        );

    ~Socket() = default;

    bool bind
        (
        const char* host,
        unsigned port,
        int flags = 0
        );

    bool listen
        (
        size_t backlog
        );

    bool accept
        (
        Socket listener
        );

    bool close
        (
        void
        );

    bool shutdown
        (
        int how
        );
    
    bool is_readable
        (
        void
        );

    bool is_writeable
        (
        void
        );

    bool send_response
        (
        const Response& response
        );

    bool write_all
        (
        const Buffer& buffer
        );

    ssize_t read
        ( 
        char* buffer, 
        size_t size,
        int flags
        );

    bool read_line
        ( 
        Buffer& buffer,
        bool append = false,
        bool crlf   = true
        );

    time_t& read_timeout
        (
        void
        );


    operator socket_t() const { return _socket; }

private:

    using Socket_Action = std::function<bool(socket_t, struct addrinfo*)>;

    socket_t    _socket;
    time_t      _read_timeout;

    static socket_t __create_socket
        (
        const char* host,
        unsigned port,
        int flags,
        Socket_Action sa
        );

    static bool __allow_reuse_address
        (
        socket_t socket
        );
        
    static int __close_socket
        (
        socket_t socket
        );

};

}

#endif  // BRIDGES_SOCKET_STREAM_H