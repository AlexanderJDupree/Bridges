///////////////////////////////////////////////////////////////////////////////
//  File    :   server_tests.cpp
//  Brief   :   Entry Po
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#include <bridges/server.h>
#include <gtest/gtest.h>

TEST(TestServerListen, ValidHostAndPort)
{
    Server server;
    EXPECT_TRUE(server.listen("localhost", 8000));
}