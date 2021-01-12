///////////////////////////////////////////////////////////////////////////////
//  File    :   utility.h
//  Brief   :   Bridges common utility function definitions
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#ifndef BRIDGES_UTILITY_H
#define BRIDGES_UTILITY_H

#include <bridges/types.h>
#include <bridges/http_status.h>

namespace bridges 
{

namespace utility
{

///////////////////////////////////////////////////////////////////////////////
// Bridges Macros
///////////////////////////////////////////////////////////////////////////////

#define CRLF "\r\n"

#define CLEAR_STRUCT(x) memset(&x, 0, sizeof(x))

/* This is super hacky but I hate the look of std::optional over Maybe <type> */
#define Maybe std::optional
#define Nothing std::nullopt

#define BRIDGES_VERSION ( fmt::format("{}.{}.{}", BRIDGES_VERSION_MAJOR  \
                                                , BRIDGES_VERSION_MINOR  \
                                                , BRIDGES_VERSION_PATCH) )

///////////////////////////////////////////////////////////////////////////////
// Global Constants
///////////////////////////////////////////////////////////////////////////////

static const std::unordered_map<Method, String> method_to_str_tbl = 
{
    { GET,        "GET"     },
    { HEAD,       "HEAD"    },
    { POST,       "POST"    },
    { PUT,        "PUT"     },
    { DELETE,     "DELETE"  },
    { CONNECT,    "CONNECT" },
    { OPTIONS,    "OPTIONS" },
    { TRACE,      "TRACE"   },
    { PATCH,      "PATCH"   },
    { INVALID,    "INVALID" }
};

static const std::unordered_map<String, Method> str_to_method_tbl = 
{
        { "GET",        GET     },
        { "HEAD",       HEAD    },
        { "POST",       POST    },
        { "PUT",        PUT     },
        { "DELETE",     DELETE  },
        { "CONNECT",    CONNECT },
        { "OPTIONS",    OPTIONS },
        { "TRACE",      TRACE   },
        { "PATCH",      PATCH   },
        { "INVALID",    INVALID }
};

///////////////////////////////////////////////////////////////////////////////
// Shared Functions
///////////////////////////////////////////////////////////////////////////////

enum class Polling_Mode {
    Read,
    Write,
    Error
};

int poll_socket
    ( 
    socket_t socket, 
    time_t timeout, 
    Polling_Mode mode
    );

bool process_request_line
    (
    const String& line,
    Request& req 
    );

bool process_header
    (
    const String& header,
    Request& req 
    );

bool has_body
    (
    const Request& req
    );

bool has_whitespace
    (
    const String& str
    );

Method read_method
    (
    const String& method
    );

String show_method
    (
    Method method
    );

Protocol_Version read_http_version
    (
    const String& version
    );

String show_http_version
    (
    Protocol_Version version
    );

String format_request_line
    (
    const Method&           method, 
    const URI&              request_uri,
    const Protocol_Version& version
    );

String format_status_line
    (
    const Protocol_Version& version,
    const Status status
    );

String format_headers
    (
    const Headers& headers
    );

} // namespace utility

} // namespace bridges

#endif // BRIDGES_UTILITY_H