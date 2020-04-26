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
    Path    document_root, 
    size_t  server_backlog,
    size_t  keep_alive_max_count,
    time_t  read_timeout
    )
: _backlog              ( server_backlog        )
, _keep_alive_max_count ( keep_alive_max_count  )
, _document_root        ( document_root         )
{
    _server_socket = INVALID_SOCKET;
    _server_socket.read_timeout() = read_timeout;

#ifdef _WIN32
    if (WSAStartup(WS_VERSION, &wsadata) != 0 )
		{
        // Windows DLL version mismatch, log error
        throw std::exception( "( Bridges ) FATAL: WSAStartup Failed." );
		}
#endif
}

bool Server::bind_to_port
    (
    const char* host, 
    unsigned port, 
    int flags
    )
{
    return _server_socket.bind(host, port, flags);
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
    if( !_server_socket.listen( _backlog ) )
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
        client_socket = accept( _server_socket, (struct sockaddr* ) &client_address, &addrlen);

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

            client_socket.close();
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

} // namespace bridges
