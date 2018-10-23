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

// 문제점
// 1. 복잡도가 올라간다. 
// 2. 모든 데이터가 미리 정의되어 있어야 한다.
//   => Junit 5는 파라미터화 테스트를 대체하는, Stream을 이용한
//      테스트가 도입되었습니다.

// class PrimeTest : public ::testing::TestWithParam<입력 데이터 타입> {
// Step 1.
class PrimeTest : public ::testing::TestWithParam<int> {
};

// Step 2.
INSTANTIATE_TEST_CASE_P(PrimeValues, PrimeTest,
	::testing::Values(7, 11, 13, 17, 31, 41));

// Step 3. TEST_F -> TEST_P
TEST_P(PrimeTest, valuesTest)
{	
	EXPECT_TRUE(isPrime(GetParam()));
}

class PrimeTest2 : public ::testing::TestWithParam<int> {
};

// Step 2.
INSTANTIATE_TEST_CASE_P(PrimeValues2, PrimeTest2,
	::testing::Values(6, 12, 15, 16));

// Step 3. TEST_F -> TEST_P
TEST_P(PrimeTest2, valuesTest)
{	
	EXPECT_FALSE(isPrime(GetParam()));
}

#if 0
TEST_F(PrimeTest, falseTest)
{
	EXPECT_FALSE(isPrime(6));
	EXPECT_FALSE(isPrime(12));
	EXPECT_FALSE(isPrime(15));
	EXPECT_FALSE(isPrime(16));
}
#endif





