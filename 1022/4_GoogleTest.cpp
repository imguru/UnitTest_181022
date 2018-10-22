// Google Test의 기능을 정리해봅시다. 
#include "gtest/gtest.h"

// 5. 테스트 비활성화
//  : 이름을 통해서 약속되어 있습니다.
//   테스트 케이스 클래스의 이름 또는 테스트 함수의 이름이
//   DISABLED_ 로 시작되면은 수행되지 않습니다. 
//    => 테스트를 주석으로 비활성화하면, 잊혀집니다. 
//    $ ./a.out --gtest_also_run_disabled_tests 
//      : 비활성화된 테스트도 같이 수행할 수 있습니다.

// 1. 단언 매크로
//   ASSERT_EQ, ASSERT_NE, ASSERT_LT, ASSERT_GT ...
// : 단언문은 하나라도 실패하면, 이후의 코드가 수행되지 않습니다.
//   => 하나의 테스트 안에는 하나의 단언문만 존재해야 한다.
//     "죽은 단언문"의 문제 때문에
//   => 하나의 테스트 안에 하나의 단언문만 있으면, 테스트가 너무
//     많아진다.
//      "유지보수성" 문제가 발생한다.
//   EXPECT_XX
// : 실패하면, 테스트는 실패하지만, 이후의 코드를 수행합니다.
TEST(GoogleTestSample, DISABLED_example1)
{
	int expected = 42;
	
	// ACT
	int actual1 = 30;
	int actual2 = 10;

	EXPECT_EQ(expected, actual1) << "Reason 1";
	EXPECT_EQ(expected, actual2) << "Reason 2";

#if 0
	ASSERT_EQ(expected, actual1) << "Reason 1";
	ASSERT_EQ(expected, actual2) << "Reason 2";
#endif
}

// 2. 문자열 비교
#include <string>
using namespace std;
// const char*

TEST(GoogleTestSample, DISABLED_example2) 
{
	string s1 = "Hello";
	string s2 = "Hello";
	
	ASSERT_EQ(s1, s2) << "s1 == s2";

	const char* s3 = "Hello";
	const char* s4 = s1.c_str();

	ASSERT_STREQ(s3, s4);
	// strcmp

	// ASSERT_EQ(s3, s4) << "s3 == s4";
	// s3 == s4
}

#include <math.h>
// 3. 부동 소수점 비교
//  : 동일한 값을 표현하는 여러가지 표현방식이 존재한다.
//  부동 소수점 타입은 절대 같거나 다름을 비교하면 안됩니다.
//   => 오차에 대한 계산을 통해 비교를 수행해야 합니다.
TEST(DISABLED_GoogleTestSample, example3)
{
	double expected = 0.7;

	double actual = 0.1 * 7;

#if 0
	if (fabs(actual - expected) < 0.0000001) {
		printf("same\n");
	}
#endif
	ASSERT_DOUBLE_EQ(expected, actual); // 4 ULP's
	// ASSERT_NEAR(expected, actual, 0.00000000001);
	ASSERT_NEAR(expected, actual, 0);

	// ASSERT_EQ(expected, actual);
}

// 4. 예외 테스트
void foo(const string& name)
{
#if 1
	if (name.empty())
		throw invalid_argument("name should not empty");
#endif
}

// foo에 빈문자열을 넘겼을 때, invalid_argument 예외가 발생해야 됩니다. 
TEST(GoogleTestSample, fooTest)
{
	string name = "";

	// EXPECT_THROW(foo(name), invalid_argument);
	
	// 예외가 발생하기만 하면 됩니다.
	EXPECT_ANY_THROW(foo(name));
}
#if 0
TEST(GoogleTestSample, fooTest)
{
	string name = "";

	try 
	{
		foo(name);
		FAIL() << "예외가 발생하지 않았습니다."; 
	}
	catch (invalid_argument& e)
	{
		SUCCEED();
	}
	catch (...)
	{
		FAIL() << "다른 예외가 발생하였습니다."; 
	}
}
#endif



















































