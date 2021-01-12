///////////////////////////////////////////////////////////////////////////////
//  File    :   server.h
//  Brief   :   Defines the Bridges HTTP Server class
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#ifndef BRIDGES_SERVER_H
#define BRIDGES_SERVER_H

#include <bridges/types.h>
#include <bridges/socket.h>
#include <bridges/request.h>
#include <bridges/response.h>

namespace bridges
{

class Server
{

public:

    Server
        ( 
        Path    document_root           = DFLT_DOCUMENT_ROOT,
        size_t  server_backlog          = DFLT_SERVER_BACKLOG,
        size_t  keep_alive_max_count    = DFLT_KEEP_ALIVE_MAX,
        time_t  read_timeout            = DFLT_READ_TIMEOUT
        );

    bool listen
        ( 
        const char*   host, 
        unsigned      port, 
        int           flags = 0
        );

    bool bind_to_port
        (
        const char* host, 
        unsigned port, 
        int flags = 0
        );
    
    Server& set_root
        (
        Path&& path
        );

    const Path& get_root
        (
        void
        );

    Server& route
        (
        const char* pattern, 
        Method methods, 
        Handler handler
        );

    Response not_found
        (
        void
        );

    void set_not_found_handler
        (
        std::function<Response(void)>
        );

private:

    static const Handler_Table      BRIDGES_DFLT_HANDLERS;

    Socket              _server_socket;
    size_t              _backlog;
    size_t              _keep_alive_max_count;
    size_t              _read_timeout_sec;
    size_t              _read_timeout_usec;
    Path                _document_root;
    Handler_Table       _handlers;

    std::function<Response(void)> _not_found;

#ifdef _WIN32
    WSADATA wsadata;    /* stores details about windows socket info */
#endif

    bool __listen
        (
        void
        );

    bool __handle_request
        ( 
        Socket client 
        );

    bool __dispatch_request
        (
        Socket client,
        const Request& request
        );

    Request __read_request
        (
        Socket client
        );

};
    
} // namespace bridges


#endif // BRIDGES_SERVER_H