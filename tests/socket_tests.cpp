///////////////////////////////////////////////////////////////////////////////
//  File    :   server_tests.cpp
//  Brief   :   Test suite for the Brides Socket Abstraction
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>

#include <bridges/socket.h>

namespace bridges {

class SocketTest : public::testing::Test {

protected:

    void TearDown() override {
        socket.close();
    }

    Socket socket;
};

TEST_F(SocketTest, DefaultConstruction) 
{
    EXPECT_EQ( socket, INVALID_SOCKET);

    time_t expected = DFLT_READ_TIMEOUT;

    EXPECT_EQ( socket.read_timeout(), expected);
}

TEST_F(SocketTest, ValidBind)
{
    EXPECT_TRUE( socket.bind("localhost", 8000) );
}

TEST_F(SocketTest, BindInvalidHost)
{
    EXPECT_FALSE( socket.bind("not a host", 8000) );
}

TEST_F(SocketTest, ListenBoundSocket)
{
    socket.bind("localhost", 8000);

    EXPECT_TRUE( socket.listen( 5 ) );
}

TEST_F(SocketTest, ListenUnboundSocket)
{
    EXPECT_FALSE( socket.listen( 5 ) );
}


}