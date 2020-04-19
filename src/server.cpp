///////////////////////////////////////////////////////////////////////////////
//  File    :   server.cpp
//  Brief   :   Bridges http server implementation
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#include <bridges/server.h>

namespace bridges
{

Server::Server(Path document_root, int server_backlog)
    : _server_fd        ( INVALID_SOCKET )
    , _document_root    ( document_root  )
    , _backlog          ( server_backlog )
{

}

bool Server::bind_to_port(const char* host, unsigned port, int flags)
{
    _server_fd = __create_socket(host, port, flags, [&](Socket sockfd, struct addrinfo* ai){
        return (::bind( sockfd, ai->ai_addr, ai->ai_addrlen ) == 0) 
            && (::listen( sockfd, _backlog ) == 0);
    });

    return _server_fd != INVALID_SOCKET;
}

bool Server::listen(const char* host, unsigned port, int flags)
{
    return bind_to_port(host, port, flags) && __listen();
}

bool Server::__listen()
{
    if(_server_fd == INVALID_SOCKET)
    {
        // TODO set error message?
        return false;
    }

    struct sockaddr_in address;
    int addrlen = sizeof(address);

    Socket new_socket = INVALID_SOCKET;

    const char *msg = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";

    while(true)
    {
        // PROTOYPE
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(_server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            // TODO log  error
            continue; 
        }
        
        char buffer[30000];

        size_t valread = read( new_socket , buffer, 30000);
        if(valread > 30000) { return false; }

        // "log" request to 
        printf("%s\n",buffer );

        size_t valwrite = write(new_socket , msg , strlen(msg));
        if(valwrite < strlen(msg)) { return false; }

        printf("------------------Hello message sent-------------------");
        close(new_socket);

        // TODO: Log connections and requests
    }
}

void Server::set_root(Path path)
{
    _document_root = path;
}

Socket Server::__create_socket(const char* host, unsigned port, int flags, Socket_Action socket_action)
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

    if (getaddrinfo(host, service.c_str(), &hints, &result) != 0) 
    {
    // TODO: log error code?
    return INVALID_SOCKET;
    }

    for (auto rp = result; rp; rp = rp->ai_next) 
    {
        // Create a socket
        Socket sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

        if (sockfd == INVALID_SOCKET) { continue; }

        // Make 'reuse address' option available
        int yes=1;

        // lose the pesky "Address already in use" error message
        if (setsockopt( sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1) {
            continue;
        } 

        if( socket_action(sockfd, rp) )
        {
            freeaddrinfo(result);
            return sockfd;
        }

        close(sockfd);
    }

    freeaddrinfo(result);
    return INVALID_SOCKET;
}

} // namespace bridges
