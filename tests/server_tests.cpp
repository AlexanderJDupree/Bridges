///////////////////////////////////////////////////////////////////////////////
//  File    :   server_tests.cpp
//  Brief   :   Entry Po
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#include <bridges/server.h>
#include <gtest/gtest.h>

namespace bridges {

TEST(TestServerBindToPort, ValidHostAndPort)
{
    Server server;
    EXPECT_TRUE(server.bind_to_port("localhost", 8000));
}

TEST(TestServerDocumentRoot, DefaultDocumentRoot)
{
    Server server;

    EXPECT_EQ( server.get_root(), "/var/www" );
}

TEST(TestServerDocumentRoot, CustomDocumentRoot)
{
    Server server;

    EXPECT_EQ( server.set_root("/www2").get_root(), "/www2");
}

} // namespace bridges