///////////////////////////////////////////////////////////////////////////////
//  File    :   server.cpp
//  Brief   :   Bridges http server implementation
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#include <bridges/server.h>

namespace bridges
{

Server::Server
    (
    Path document_root, 
    int server_backlog
    )
: _server_fd        ( INVALID_SOCKET )
, _backlog          ( server_backlog )
, _document_root    ( document_root  )
{

}

bool Server::bind_to_port
    (
    const char* host, 
    unsigned port, 
    int flags
    )
{
    _server_fd = __create_socket(host, port, flags, [&](Socket sockfd, struct addrinfo* ai){
        return bind( sockfd, ai->ai_addr, ai->ai_addrlen ) == 0;
    } );

    return _server_fd != INVALID_SOCKET;
}

bool Server::listen
    (
    const char* host, 
    unsigned port, 
    int flags
    )
{
    return bind_to_port(host, port, flags) && __listen();
}

bool Server::__listen
    (
    void
    )
{
    if( ::listen(_server_fd, _backlog ) != 0)
    {
        // TODO set error message?
        return false;
    }

    struct sockaddr_storage client_address;
    socklen_t addrlen = sizeof( client_address );

    Socket client_socket = INVALID_SOCKET;

    const char *msg = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";

    while(true)
    {
        // Accept is a blocking call
        client_socket = accept( _server_fd, (struct sockaddr* ) &client_address, &addrlen);

        if( client_socket != INVALID_SOCKET )
        {
            size_t total_bytes = 0;
            const size_t FIXED_BUFFER_SIZE = 30000;
            Buffer buffer;
            char fixed_buffer[FIXED_BUFFER_SIZE];
            memset( fixed_buffer, '\0', sizeof( fixed_buffer ) );
           
            bool receiving = true;
            while ( receiving )
            {
                size_t nbytes = recv( client_socket, fixed_buffer, FIXED_BUFFER_SIZE - 1, 0);

                if(nbytes <= 0)
                {
                    if(nbytes == 0)
                    {
                        // Socket closed 
                        return false;
                    }
                    // -1, error occured
                    return false;
                }
                else
                {
                    total_bytes += nbytes;
                    buffer += fixed_buffer;

                    if(total_bytes < FIXED_BUFFER_SIZE)
                    {
                        receiving = false;
                    }
                }
            }

            printf("%s\n", buffer.c_str());

            size_t valwrite = send(client_socket, msg, strlen(msg), 0);
            if(valwrite < strlen(msg)) { return false; }

            shutdown(client_socket, SHUT_RDWR);
        }

        // TODO: Log connections and requests
    }
}

Server& Server::set_root
    (
    Path&& path
    )
{
    _document_root = path;
    return *this;
}

const Path& Server::get_root
    (
    void
    )
{
    return _document_root;
}

Socket Server::__create_socket
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

    clear_struct(hints);

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
    Socket sockfd = INVALID_SOCKET;
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

bool Server::__allow_reuse_address
    (
    Socket socket
    )
{
    int yes=1;

    return setsockopt( socket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char*>(&yes), sizeof( yes ) ) == 0;
}

int Server::__close_socket
    (
    Socket socket
    )
{
#ifdef _WIN32
    return closesocket( socket );
#else 
    return close( socket );
#endif
}

} // namespace bridges
