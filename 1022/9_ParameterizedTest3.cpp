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

struct Data
{
	int input;
	bool result;
	
	Data(int i, bool r) : input(i), result(r) {}
};

class PrimeTest : public ::testing::TestWithParam<Data> {
};

INSTANTIATE_TEST_CASE_P(PrimeValues, PrimeTest,
	::testing::Values(
		Data(1, false),
		Data(3, true),
		Data(5, true)
	));

TEST_P(PrimeTest, valuesTest)
{	
	Data data = GetParam();
	EXPECT_EQ(data.result, isPrime(data.input));
}













