///////////////////////////////////////////////////////////////////////////////
//  File    :   server.cpp
//  Brief   :   Bridges http server implementation
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#include <bridges/socket.h>
#include <bridges/utility.h>
#include <bridges/response.h>

namespace bridges
{

Socket::Socket
    (
    socket_t    socket,
    time_t      read_timeout
    )
: _socket           ( socket       )
, _read_timeout     ( read_timeout )
{
}


time_t& Socket::read_timeout
    (
    void
    )
{
    return _read_timeout;
}


bool Socket::bind
    (
    const char* host,
    unsigned port,
    int flags
    )
{
    _socket =__create_socket(host, port, flags, [&](socket_t sock, struct addrinfo* ai){
        return ::bind( sock, ai->ai_addr, ai->ai_addrlen ) == 0;
    } );

    return _socket != INVALID_SOCKET;
}


bool Socket::listen
    (
    size_t backlog
    )
{
    return ::listen(_socket, backlog) == 0;
}


bool Socket::accept
    (
    Socket listener
    )
{
    //struct sockaddr_storage client_address;
    //socklen_t addrlen = sizeof( client_address );

    _socket = ::accept( listener, nullptr, nullptr );

    return _socket != INVALID_SOCKET;
}


bool Socket::close
    (
    void
    )
{
    return __close_socket(_socket) == 0;
}


bool Socket::shutdown
    (
    int how
    )
{
    return ::shutdown(_socket, how) == 0;
}


bool Socket::is_readable
    (
    void
    )
{
    return utility::poll_socket(_socket, _read_timeout, utility::Polling_Mode::Read) > 0;
}


bool Socket::is_writeable
    (
    void
    )
{
    return utility::poll_socket(_socket, _read_timeout, utility::Polling_Mode::Write) > 0;
}


bool Socket::send_response
    (
    const Response& resp
    )
{
    return write_all( resp.to_string() );
}


bool Socket::write_all
    (
    const Buffer& msg
    )
{
    ssize_t sent = 0;
    ssize_t total = msg.length();
    const char* buffer = msg.c_str();


    for( ssize_t i = 0; i >= 0 && sent < total; )
    {
        i = send( _socket, buffer + i, total - sent, 0);
        sent += i;
    }
    return (sent < total) ? false : true;
}


ssize_t Socket::read
    (
    char* buffer, 
    size_t size,
    int flags
    )
{
    return recv( _socket, buffer, size, flags);
}


bool Socket::read_line( Buffer& buffer, bool append, bool crlf)
{
    if(!append) 
    {
        buffer.clear();
    }

    char    byte = '\0';
    size_t  nbytes = 0;
    size_t  size = buffer.size();

    // Read a byte at a time until newline
    while( read(&byte, 1, 0) > 0 && ++nbytes <= BRIDGES_HTTP_MAX_LINE_LENGTH && byte != '\n' )
    {
        buffer += byte;
    }

    if( crlf && !buffer.empty() ) { buffer.pop_back(); } // Discard '\r'

    return buffer.size() > size; // Read occured
}


socket_t Socket::__create_socket
    (
    const char* host,
    unsigned port,
    int flags,
    Socket_Action socket_action
    )
{ 
    // Get address info
    struct addrinfo hints;
    struct addrinfo *result;

    CLEAR_STRUCT(hints);

    hints.ai_family   = AF_UNSPEC;    // Ipv4 or Ipv6
    hints.ai_socktype = SOCK_STREAM;  // TCP only
    hints.ai_flags    = flags;
    hints.ai_protocol = 0;            // Allow any protocol

    auto service = std::to_string(port);

    if ( getaddrinfo( host, service.c_str(), &hints, &result ) != 0 ) 
    {
        // TODO: log error code?
        return INVALID_SOCKET;
    }

    bool success = false;
    socket_t sockfd = INVALID_SOCKET;

    // Scan through results and attempt to create a socket
    for ( auto rp = result; rp && !success; rp = rp->ai_next ) 
    {
        // Create a socket
        sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

        if (sockfd == INVALID_SOCKET) { continue; }

        success = __allow_reuse_address( sockfd ) && socket_action( sockfd, rp);
        if( !success )
        {
            __close_socket( sockfd );
            sockfd = INVALID_SOCKET;
        }
    }

    freeaddrinfo(result);
    return sockfd;
}

bool Socket::__allow_reuse_address
    (
    socket_t socket
    )
{
    int yes=1;

    return setsockopt( socket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char*>(&yes), sizeof( yes ) ) == 0;
}

int Socket::__close_socket
    (
    socket_t socket
    )
{
#ifdef _WIN32
    return closesocket( socket );
#else 
    return ::close( socket );
#endif
}

}