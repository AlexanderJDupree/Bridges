///////////////////////////////////////////////////////////////////////////////
//  File    :   server_tests.cpp
//  Brief   :   Test suite for the Bridges Server
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#include <bridges/server.h>
#include <gtest/gtest.h>

namespace bridges {

class ServerTest : public::testing::Test {

protected:

    Server server;

};

TEST_F(ServerTest, ValidBindToPort)
{
    EXPECT_TRUE(server.bind_to_port("localhost", 8000));
}

TEST_F(ServerTest, DefaultDocumentRoot)
{
    EXPECT_EQ( server.get_root(), "/var/www" );
}

TEST_F(ServerTest, CustomDocumentRoot)
{
    EXPECT_EQ( server.set_root("/www2").get_root(), "/www2");
}

} // namespace bridges