///////////////////////////////////////////////////////////////////////////////
//  File    :   server_tests.cpp
//  Brief   :   Entry Po
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#include <bridges/server.h>
#include <gtest/gtest.h>

using namespace bridges;

TEST(TestServerBindToPort, ValidHostAndPort)
{
    Server server;
    EXPECT_TRUE(server.bind_to_port("localhost", 8000));
}