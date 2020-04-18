///////////////////////////////////////////////////////////////////////////////
//  File    :   server.cpp
//  Brief   :   Bridges http server implementation
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#include <bridges/server.h>

namespace bridges
{

Server::Server()
    : _server_fd(INVALID_SOCKET)
{

}

bool Server::bind_to_port(const char* host, int port, int flags)
{
    return true;
}

bool Server::listen(const char* host, int port, int flags)
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
    return true;
}

} // namespace bridges
