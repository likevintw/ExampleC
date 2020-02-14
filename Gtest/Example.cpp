#include "pch.h"

int Max(int a, int b)
{
    if (b > a)
    {
        a = b;
    }
    return a;
}
int Sum(int a, int b)
{
    return a + b;
}
TEST(Max, TestMax) {
    EXPECT_EQ(10, Max(3,10));
    EXPECT_TRUE(true);
}


TEST(Sum, TextSum) 
{
    for (int i(0); i < 10; i++)
    {
        EXPECT_EQ(i+10, Sum(i, 10));
    } 
    EXPECT_TRUE(true);
}
