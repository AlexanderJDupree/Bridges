///////////////////////////////////////////////////////////////////////////////
//  File    :   server.h
//  Brief   :   Defines the Bridges HTTP Server class
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#ifndef BRIDGES_SERVER_H
#define BRIDGES_SERVER_H

#include <functional>
#include <bridges/defs.h>
#include <bridges/socket.h>
#include <bridges/request.h>
#include <bridges/response.h>

namespace bridges
{

static constexpr Method GET     =   0x1 << 0;
static constexpr Method HEAD    =   0x1 << 1;
static constexpr Method POST    =   0x1 << 2;
static constexpr Method PUT     =   0x1 << 3;
//static constexpr Method DELETE  =   0x1 << 4;
static constexpr Method CONNECT =   0x1 << 5;
static constexpr Method OPTIONS =   0x1 << 6;
static constexpr Method TRACE   =   0x1 << 7;
static constexpr Method PATCH   =   0x1 << 8;

using Handler = std::function<Response(const Request&)>;

class Server
{
public:

    Server
        ( 
        Path    document_root           = DFLT_DOCUMENT_ROOT,
        size_t  server_backlog          = DFLT_SERVER_BACKLOG,
        size_t  keep_alive_max_count    = DFLT_KEEP_ALIVE_MAX,
        size_t  read_timeout_sec        = DFLT_READ_TIMEOUT_SEC,
        size_t  read_timeout_usec       = DFLT_READ_TIMEOUT_USEC
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

private:

    using Socket_Action = std::function<bool(Socket, struct addrinfo*)>;

    Socket  _server_socket;
    size_t  _backlog;
    size_t  _keep_alive_max_count;
    size_t  _read_timeout_sec;
    size_t  _read_timeout_usec;
    Path    _document_root;

#ifdef _WIN32
    WSADATA wsadata;    /* stores details about windows socket info */
#endif

    bool __listen
        (
        void
        );

    bool __allow_reuse_address
        ( 
        Socket socket
        );

    Socket __create_socket
        (
        const char* host, 
        unsigned port, 
        int flags, 
        Socket_Action sa
        );

    int __close_socket
        (
        Socket socket
        );
};

    
} // namespace bridges


#endif // BRIDGES_SERVER_H