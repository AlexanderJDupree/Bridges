///////////////////////////////////////////////////////////////////////////////
//  File    :   server.h
//  Brief   :   Defines the Bridges HTTP Server class
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#ifndef BRIDGES_SERVER_H
#define BRIDGES_SERVER_H

#include <bridges/defs.h>

class Server
{
public:

    Server();

    bool listen(const char* host, int port, int flags = 0);
    bool bind_to_port(const char* host, int port, int flags = 0);

private:

    socket_t _server_fd;

    bool __listen();
};

#endif // BRIDGES_SERVER_H