///////////////////////////////////////////////////////////////////////////////
//  File    :   server.cpp
//  Brief   :   Bridges http server implementation
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#include <bridges/server.h>
#include <bridges/utility.h>

namespace bridges
{

static const Request_Handler Bad_Request_400 {
    .route = "*",
    .action = [](const Request&, Response& resp){
        Headers headers;
        headers.data = {
            { "Server", "bridges-" + BRIDGES_VERSION },
            { "Status", "400 bad request" },
            { "Content-Type", "text/html; charset=utf-8"},
        };
        resp = Response(
            Status::Bad_Request,
            headers, 
            {1, 1 },
            "<header>400 Bad Request</header>"
        );
    }
};

const Handler_Table Server::BRIDGES_DFLT_HANDLERS = 
{
    { INVALID, { Bad_Request_400 } }
};

Server::Server
    (
    Path    document_root, 
    size_t  server_backlog,
    size_t  keep_alive_max_count,
    time_t  read_timeout
    )
: _backlog              ( server_backlog            )
, _keep_alive_max_count ( keep_alive_max_count      )
, _document_root        ( document_root             )
, _handlers             ( BRIDGES_DFLT_HANDLERS     )
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

    _not_found = [](){
        // TODO: Add date header
        Headers headers;
        headers.data = {
            { "Server", "bridges-" + BRIDGES_VERSION },
            { "Status", "404 not found" },
            { "Content-Type", "text/html; charset=utf-8"},
        };

        return Response(
            Status::Not_Found,
            headers, 
            {1, 1 },
            "<header>404 Not Found</header>"
        );
    };
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
    // TODO: thread pool management stuff here

    // TODO: don't close client if directed to keep-alive
    return __dispatch_request( client, __read_request( client ) ) && client.close();
}

bool Server::__dispatch_request
    (
    Socket client,
    const Request& request
    )
{
    for ( const auto& handler : _handlers[request.method] )
    {
        if( std::regex_match( request.target, std::regex(handler.route) ) )
        {
            Response response;

            handler.action( request, response );

            return client.write_all( response.to_string() );
        }
    }
    return client.write_all( _not_found().to_string() );
    
    Buffer msg = "HTTP/1.1 200 OK\nServer: bridges-0.2.0\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!\n"; 

    return client.write_all(msg) && client.close();
}

// TODO: benchmark performance of this compared to passing in an out parameter to modify
Request Server::__read_request
    (
    Socket client
    )
// TODO: Review Compliance with https://tools.ietf.org/html/rfc7230#section-3
{
    using namespace utility;

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
    return Request(); // Default Request will trigger a 400 response
}

void Server::set_not_found_handler
    (
    std::function<Response(void)> handler
    )
{
    _not_found = handler;
}

} // namespace bridges
