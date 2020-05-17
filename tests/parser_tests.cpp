///////////////////////////////////////////////////////////////////////////////
//  File    :   parser_tests.cpp
//  Brief   :   Test suite for the Brides parsing utilities
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#include <bridges/common.h>
#include <bridges/request.h>

#include <gtest/gtest.h>

namespace bridges 
{

class ParsersTest : public::testing::Test {

protected:
    void SetUp() override {
        request = Request();
    }

    Request request;
};

TEST_F(ParsersTest, ReadMethodInvalidToken)
{
    EXPECT_EQ(read_method("not a method"), INVALID);
}

TEST_F(ParsersTest, ReadMethodTokensWithWhitespace)
{
    EXPECT_EQ(read_method("GET "), INVALID);
    EXPECT_EQ(read_method(" GET"), INVALID);
    EXPECT_EQ(read_method("G ET"), INVALID);
}

TEST_F(ParsersTest, ReadMethodValidTokens)
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

    for ( auto method : table )
    {
        EXPECT_EQ(read_method(method.first), method.second);
    }
}

TEST_F(ParsersTest, ReadHttpVersionValidString)
{
    Protocol_Version expected { 1, 1};
    EXPECT_EQ(read_http_version("HTTP/1.1"), expected);
}

TEST_F(ParsersTest, ReadHttpVersionWhitespace)
{
    Protocol_Version expected { 0, 0};
    EXPECT_EQ(read_http_version("HTTP / 1.1"), expected);
    EXPECT_EQ(read_http_version("HTTP/1 . 1"), expected);
    EXPECT_EQ(read_http_version(" HTTP/1.1 "), expected);
}

TEST_F(ParsersTest, ReadHttpVersionLeadingZeroes)
{
    Protocol_Version expected { 1, 1};
    EXPECT_EQ(read_http_version("HTTP/01.1"), expected);
    EXPECT_EQ(read_http_version("HTTP/1.001"), expected);
}

TEST_F(ParsersTest, ReadHttpVersionMultiDigitVersions)
{
    Protocol_Version expected { 12, 13};
    EXPECT_EQ(read_http_version("HTTP/12.13"), expected);
}

TEST_F(ParsersTest, ProcessRequestLineValidLine)
{
    Protocol_Version expected { 1, 1 };
    String request_line = "GET / HTTP/1.1";
    EXPECT_EQ(process_request_line(request_line, request), true);

    EXPECT_EQ(request.method, GET);
    EXPECT_EQ(request.target, "/");
    EXPECT_EQ(request.version, expected);
}

TEST_F(ParsersTest, ProcessRequestLineInvalidMethod)
{
    Protocol_Version expected { 1, 1 };
    String request_line = "TRASH / HTTP/1.1";
    EXPECT_EQ(process_request_line(request_line, request), false);

    EXPECT_EQ(request.method, INVALID);
    EXPECT_EQ(request.target, "/");
    EXPECT_EQ(request.version, expected);
}

TEST_F(ParsersTest, ProcessRequestLineInvalidVersion)
{
    Protocol_Version expected { 1, 0 };
    String request_line = "GET / HTTP/1.0";
    EXPECT_EQ(process_request_line(request_line, request), false);

    EXPECT_EQ(request.method, GET);
    EXPECT_EQ(request.target, "/");
    EXPECT_EQ(request.version, expected);
}

TEST_F(ParsersTest, ProcessRequestLineInvalidLine)
{
    Protocol_Version expected { 0, 0 };
    String request_line = "not a request line";
    EXPECT_EQ(process_request_line(request_line, request), false);

    EXPECT_EQ(request.method, INVALID);
    EXPECT_EQ(request.target, "");
    EXPECT_EQ(request.version, expected);
}

TEST_F(ParsersTest, ProcessHeaderValidHeader)
{
    String header = "accept-encoding: gzip, deflate, br";

    EXPECT_EQ( process_header( header, request ), true );
    EXPECT_EQ( request.headers["accept-encoding"], "gzip, deflate, br");
}

TEST_F(ParsersTest, ProcessHeaderWithWhitespace)
{
    String wsBetweenDelimeter           = "accept-encoding : gzip, deflate, br";
    String wsBeforeFieldName            = " accept-encoding: gzip, deflate, br";
    String leadingWSBeforeFieldValue    = "accept-encoding:    \t\t  gzip, deflate, br";

    EXPECT_EQ( process_header( wsBetweenDelimeter, request ), false );
    EXPECT_EQ( process_header( wsBeforeFieldName, request ), false );
    EXPECT_EQ( process_header( leadingWSBeforeFieldValue, request ), true );

    EXPECT_EQ( request.headers["accept-encoding"], "gzip, deflate, br");
}
    
} // namespace bridges
