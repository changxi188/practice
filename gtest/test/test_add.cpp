#include <gtest/gtest.h>

#include <iostream>

#include "add1.h"

using namespace std;

bool test_aa()
{
    return true;
}
bool test_bb()
{
    int a = 0;
    return true;
}

TEST(balTest, aaa)
{
    EXPECT_EQ(Add::GetRes(-1), 1);
    EXPECT_EQ(Add::GetRes(3), 1);
}

TEST(fTest, bbb)
{
    EXPECT_FALSE(test_aa);
    EXPECT_TRUE(test_bb);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
