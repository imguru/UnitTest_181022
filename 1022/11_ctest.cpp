// #include "foo.h"
// int add(int a, int b);

#include "foo.c"

#include "gtest/gtest.h"

TEST(CTest, addTest)
{
	ASSERT_EQ(42, add(10, 32));
}
