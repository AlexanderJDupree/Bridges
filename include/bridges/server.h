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
#include <bridges/request.h>
#include <bridges/response.h>

namespace bridges
{

using Handler = std::function<Response(const Request&)>;

class Server
{
public:

    Server();

    bool listen(const char* host, int port, int flags = 0);
    bool bind_to_port(const char* host, int port, int flags = 0);
    
    void set_root(const char* path);

    void route(const char* pattern, Method methods, Handler handler);

private:

    socket_t _server_fd;

    bool __listen();
};

    
} // namespace bridges


#endif // BRIDGES_SERVER_H