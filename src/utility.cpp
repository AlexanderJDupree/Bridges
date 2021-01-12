///////////////////////////////////////////////////////////////////////////////
//  File    :   server_tests.cpp
//  Brief   :   Test suite for the Bridges Server
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#include <bridges/utility.h>
#include <bridges/request.h>
#include <bridges/headers.h>

namespace bridges 
{

namespace utility
{


int poll_socket
    ( 
    socket_t socket, 
    time_t timeout, 
    Polling_Mode mode
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
    case Polling_Mode::Read:
        return select(nfds, &fds, NULL, NULL, reinterpret_cast<timeval*>(&timeout));

    case Polling_Mode::Write:
        return select(nfds, nullptr, &fds, nullptr, reinterpret_cast<timeval*>(&timeout));

    case Polling_Mode::Error:
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
// TODO: Review Compliance with https://tools.ietf.org/html/rfc7230#section-3.1.1
{
    Tokens tokens;
    strtk::split(' ', line, strtk::range_to_type_back_inserter(tokens));

    if(tokens.size() != 3) { return false; }

    req.method  = read_method(tokens[0]);
    req.target  = tokens[1]; // TODO: only set target if method and version are valid
    req.version = read_http_version(tokens[2]);

    // TODO: Currently only support HTTP version 1.1
    return req.method != INVALID && req.version.major == 1 && req.version.minor == 1;
}

Method read_method
    (
    const String& method
    )
{
    try
    {
        return str_to_method_tbl.at(method);
    }
    catch(...)
    {
        return INVALID;
    }
}

String show_method
    (
    Method method
    )
{
    try
    {
        return method_to_str_tbl.at(method);
    }
    catch(...)
    {
        return "INVALID";
    }
}


Protocol_Version read_http_version
    (
    const String& version
    )
{
    int major = 0;
    int minor = 0;

    strtk::parse( version
                , "/."
                , strtk::expect("HTTP").ref()
                , major
                , minor
                );

    // Returns {0,0} if parser fails
    return { static_cast<uint8_t>(major), static_cast<uint8_t>(minor) };
}

String show_http_version
    (
    Protocol_Version version
    )
{
    return fmt::format("HTTP/{}.{}", version.major, version.minor);
}

bool process_header
    (
    const String& header,
    Request& req 
    )
// TODO: Review Compliance with https://tools.ietf.org/html/rfc7230#section-3.2
{ 
    String field_name;
    String field_value;

    bool status = strtk::parse( header
                              , ":" 
                              , field_name
                              , strtk::trim_leading(" \t\v", field_value).ref()
                              );

    if ( status && (status = !has_whitespace( field_name )) )
    {
        req.headers.append( std::forward<String>(field_name), std::forward<String>(field_value) );
    }
    return status;
}

bool has_body
    (
    const Request& req
    )
{
    return false;
}

bool has_whitespace
    (
    const String& str
    )
{
    return std::find_if(str.begin(), str.end(), [](char c){
        return std::isspace(c);
    }) != str.end();
}


String format_request_line
    (
    const Method&           method, 
    const URI&              request_uri,
    const Protocol_Version& version
    )
{
    return fmt::format( "{} {} HTTP/{}.{}\r\n", show_method( method )
                                              , request_uri
                                              , version.major
                                              , version.minor );
}

String format_status_line
    (
    const Protocol_Version& version,
    const Status status
    )
{
    return fmt::format( "HTTP/{}.{} {} {}\r\n", version.major
                                              , version.minor
                                              , static_cast<int>( status )
                                              , status_to_str_tbl.at( status ) );
}

String format_headers
    (
    const Headers& headers
    )
{
    String output;
    for (const auto& header : headers.data)
    {
        output += fmt::format("{}: {}\r\n", header.first, header.second);
    }
    return output;
}

} //namespace utility

} // namespace bridges
