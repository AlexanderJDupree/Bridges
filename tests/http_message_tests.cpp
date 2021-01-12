///////////////////////////////////////////////////////////////////////////////
//  File    :   utility_tests.cpp
//  Brief   :   Test suite for the Brides utility functions
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#include <bridges/utility.h>
#include <bridges/request.h>
#include <bridges/response.h>

#include <gtest/gtest.h>

namespace bridges 
{

TEST(RequestTests, EmptyRequestToString)
{
    const String expected   = "INVALID  HTTP/0.0\r\n\r\n";
    const String actual     = Request().to_string();

    EXPECT_EQ( expected, actual);
}

// NOTE: headers are currently alphabetically ordered and do not care about the order 
// to which they were added to the map
TEST(RequestTests, ValidRequestToString)
{
    Request req;
    req.method       = GET;
    req.target       = "/";
    req.version      = {1, 1};
    req.headers.data = {
        { "Host", "google.com"},
        { "Connection", "keep-alive" }
    };

    const String expected   = "GET / HTTP/1.1\r\nConnection: keep-alive\r\nHost: google.com\r\n\r\n";

    EXPECT_EQ( expected, req.to_string() );
}

TEST(ResponseTests, EmptyResponseToString)
{
    const String expected   = "HTTP/0.0 501 Not Implemented\r\n\r\n";
    const String actual     = Response().to_string();

    EXPECT_EQ( expected, actual);
}

TEST(RequestTests, ValidResponseToString)
{
    Response resp;
    resp.status        = Status::OK;
    resp.version       = {1, 1};
    resp.headers.data  = {
        { "Server",         "bridges-0.2.0" },
        { "Content-Type",   "text/plain"    },
        { "Content-Length", "12"            }
    };
    resp.body = "Hello World!";


    const String expected = "HTTP/1.1 200 OK\r\nContent-Length: 12\r\nContent-Type: text/plain\r\nServer: bridges-0.2.0\r\n\r\nHello World!"; 

    EXPECT_EQ( expected, resp.to_string() );
}


}
