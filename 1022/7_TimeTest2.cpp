#include "gtest/gtest.h"
#include <time.h>

// C++: 같은 제네릭 인자를 전달 받으면, 동일 타입이다.
//  TimeoutTest<2> 
//  CRTP: Curiosly Recurring Template Pattern

template <typename T, int N>
class TimeoutTest : public ::testing::Test {
protected:
	time_t startTime;
	static const int PIVOT_SECONDS = N;

	virtual void SetUp() {
		startTime = time(0);
	}

	virtual void TearDown() {
		time_t endTime = time(0);
		time_t duration = endTime - startTime;

		EXPECT_TRUE(duration < PIVOT_SECONDS) << "Timeout: " << duration;
	}
};

class Timeout2Seconds : public TimeoutTest<Timeout2Seconds, 2> {

};

class Timeout4Seconds : public TimeoutTest<Timeout4Seconds, 4> {

};

void foo()
{
	sleep(3);
}

// 아래의 테스트는 반드시 2초 안에 수행되어야 합니다.
TEST_F(Timeout2Seconds, sample)
{
	foo();
}

TEST_F(Timeout4Seconds, sample)
{
	foo();
}




