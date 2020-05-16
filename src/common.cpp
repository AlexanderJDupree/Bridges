///////////////////////////////////////////////////////////////////////////////
//  File    :   server_tests.cpp
//  Brief   :   Test suite for the Bridges Server
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#include <iterator>
#include <strtk.hpp>
#include <bridges/common.h>
#include <bridges/request.h>

namespace bridges 
{

int poll_socket
    ( 
    socket_t socket, 
    time_t timeout, 
    SELECT_MODE mode
    )
{
// TODO: poll() or select()? Or make configurable 
// TODO: Allow for multiple sockets to be polled and return a list of ready sockets 

fd_set fds;
FD_ZERO(&fds);
FD_SET(socket, &fds);
int nfds = socket + 1; // See select manual for derivation of this value

switch ( mode )
    {
    case SELECT_MODE::READ_FDS:
        return select(nfds, &fds, NULL, NULL, reinterpret_cast<timeval*>(&timeout));
    case SELECT_MODE::WRITE_FDS:
        return select(nfds, nullptr, &fds, nullptr, reinterpret_cast<timeval*>(&timeout));
    case SELECT_MODE::ERROR_FDS:
        return select(nfds, nullptr, nullptr, &fds, reinterpret_cast<timeval*>(&timeout));
    default:
        return -1;
    }
}

bool process_request_line
    (
    const String& line,
    Request& req 
    )
{
    Tokens tokens;
    strtk::split(' ', line, strtk::range_to_type_back_inserter(tokens));

    if(tokens.size() < 3) { return false; }

    req.method  = read_method(tokens[0]);
    req.target  = tokens[1];
    req.version = read_http_version(tokens[2]);

    // TODO: Currently only support HTTP version 1.1
    return req.method != INVALID && req.version.major == 1 && req.version.minor == 1;
}

Method read_method
    (
    const String& method
    )
{
    using Method_Table = std::map<String, Method>;
    Method_Table table {
        { "GET",        GET     },
        { "HEAD",       HEAD    },
        { "POST",       POST    },
        { "PUT",        PUT     },
        { "DELETE",     DELETE  },
        { "CONNECT",    CONNECT },
        { "OPTIONS",    OPTIONS },
        { "TRACE",      TRACE   },
        { "PATCH",      PATCH   },
    };
    try
    {
        return table.at(method);
    }
    catch(const std::out_of_range&)
    {
        return INVALID;
    }
}

Protocol_Version read_http_version
    (
    const String& version
    )
{
    Tokens tokens;
    strtk::split('/', version, strtk::range_to_type_back_inserter(tokens));

    if(tokens.size() == 2 && tokens[0] == "HTTP") { 

        Tokens version_tokens;
        strtk::split('.', tokens[1], strtk::range_to_type_back_inserter(version_tokens));
        if(version_tokens.size() == 2)
        {
            try
            {   
                uint8_t major = std::stoi(version_tokens[0]);
                uint8_t minor = std::stoi(version_tokens[1]);
                return { major, minor };
            }
            catch(const std::exception&)
            {
                // Fall through
            }
        }
    }
    return { 0, 0};
}

bool process_header
    (
    const Buffer& buff,
    Request& req 
    )
{ 
    return false;
}

bool has_body
    (
    const Request& req
    )
{
    return false;
}

}