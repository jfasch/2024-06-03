#include <gtest/gtest.h>


TEST(demo, pass)
{
    ASSERT_EQ(1+1, 2);
}

TEST(demo, fail)
{
    ASSERT_EQ('X', 'U');
}
