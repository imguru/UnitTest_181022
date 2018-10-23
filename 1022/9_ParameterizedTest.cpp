
// 9_Parameterized Test
//  xUnit Test Pattern: Framework 지원
//  : 입력 데이터를 바꿔가면서, 수차례 반복 검사하는 데이터 중심
//    테스트에서 코드의 중복을 없애주는 기법.

bool isPrime(int value)
{
	if (value == 0 || value == 1)
		return false;

	for (int i = 2 ; i < value ; ++i)
		if (value % i == 0)
			return false;

	return true;
}

#include "gtest/gtest.h"

class PrimeTest : public ::testing::Test {

};

TEST_F(PrimeTest, valuesTest)
{	
	int data[] = { 7, 11, 13, 17, 31 };
	for (int i = 0 ; i < 5; ++i)
		ASSERT_TRUE(isPrime(31));
}

TEST_F(PrimeTest, falseTest)
{
	ASSERT_FALSE(isPrime(6));
	ASSERT_FALSE(isPrime(12));
	ASSERT_FALSE(isPrime(15));
	ASSERT_FALSE(isPrime(16));
}

#if 0
TEST_F(PrimeTest, valuesTest)
{	
	EXPECT_TRUE(isPrime(7));
	EXPECT_TRUE(isPrime(11));
	EXPECT_TRUE(isPrime(13));
	EXPECT_TRUE(isPrime(17));
	EXPECT_TRUE(isPrime(31));
}

TEST_F(PrimeTest, falseTest)
{
	EXPECT_FALSE(isPrime(6));
	EXPECT_FALSE(isPrime(12));
	EXPECT_FALSE(isPrime(15));
	EXPECT_FALSE(isPrime(16));
}
#endif





