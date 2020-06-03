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

    Socket client_socket;

    while(client_socket.accept(_server_socket))
    {
        if( client_socket != INVALID_SOCKET )
        {
            __handle_request( client_socket );
        }

        // TODO: Log connections and requests
    }
    return true;
}


bool Server::__handle_request( Socket client)
{
    if ( Maybe<Request> req = __read_request( client ) )
    {
        return dispatch_request( client, req.value() );
    }

    // client.send_response( bad_request_handler() );
    Buffer msg = "HTTP/1.1 400 Bad Request\nServer: bridges-0.2.0\nContent-Type: text/plain\nContent-Length: 24\n\nSo. . . That didn't work\n";
    return client.write_all(msg) && client.close();
}

bool Server::dispatch_request
    (
    Socket client,
    const Request& request
    )
{
    // Lookup handlers

    // client.send_response( handler(request) );
    
    Buffer msg = "HTTP/1.1 200 OK\nServer: bridges-0.2.0\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!\n"; 

    return client.write_all(msg) && client.close();
}

Maybe<Request> Server::__read_request
    (
    Socket client
    )
// TODO: Review Compliance with https://tools.ietf.org/html/rfc7230#section-3
{
    Buffer  buffer;
    Request req;

    if( client.read_line( buffer) && process_request_line( buffer, req))
    {
        size_t nbytes = buffer.size();
        while( client.read_line( buffer ) && process_header( buffer, req) && nbytes < BRIDGES_HTTP_MAX_REQUEST_SIZE)
        {
            nbytes += buffer.size();
        }

        if( has_body( req ))
        {
            // Process body
        }
        // verify headers first??
        return req;
    }
    return Nothing;
}

} // namespace bridges
