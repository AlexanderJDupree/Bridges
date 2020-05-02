///////////////////////////////////////////////////////////////////////////////
//  File    :   server_tests.cpp
//  Brief   :   Test suite for the Bridges Server
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#include <bridges/common.h>


namespace bridges 
{


int poll_socket( socket_t socket, time_t timeout, SELECT_MODE mode)
{
// TODO: poll() or select()? Or make configurable 
// TODO: Allow for multiple sockets to be polled and return a list of ready sockets 

fd_set fds;
FD_ZERO(&fds);
FD_SET(socket, &fds);
int nfds = socket + 1; // See select manual for derivation of this value

switch ( mode )
    {
    case SELECT_MODE::READ :
        return select(nfds, &fds, NULL, NULL, reinterpret_cast<timeval*>(&timeout));
    case SELECT_MODE::WRITE :
        return select(nfds, nullptr, &fds, nullptr, reinterpret_cast<timeval*>(&timeout));
    case SELECT_MODE::ERROR :
        return select(nfds, nullptr, nullptr, &fds, reinterpret_cast<timeval*>(&timeout));
    default:
        return -1;
    }
}

bool ends_with(const std::string& str, const std::string& suffix)
{
    return str.size() >= suffix.size() && 0 == str.compare(str.size()-suffix.size(), suffix.size(), suffix);
}

bool starts_with(const std::string& str, const std::string& prefix)
{
    return str.size() >= prefix.size() && 0 == str.compare(0, prefix.size(), prefix);
}

}