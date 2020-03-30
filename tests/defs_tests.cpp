///////////////////////////////////////////////////////////////////////////////
//  File    :   defs_tests.cpp
//  Brief   :   Entry Point for GTest suite
//  Author  :   Alexander DuPree
///////////////////////////////////////////////////////////////////////////////

#include <bridges/defs.h>
#include <gtest/gtest.h>


TEST(DefsTest, sampleTest1)
{
    EXPECT_EQ(BRIDGES_VERSION_MAJOR, 0);
}
TEST(DefsTest, sampleTest2)
{
    EXPECT_EQ(BRIDGES_VERSION_MINOR, 1);
}
TEST(DefsTest, sampleTest3)
{
    EXPECT_EQ(BRIDGES_VERSION_PATCH, 0);
}
