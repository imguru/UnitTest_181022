#include "gtest/gtest.h"
#include <time.h>

// 비기능 테스트 
//   : 시간, 메모리 등의 요소를 통해 테스트의 결과를 측정하는 방법
// => JUnit은 시간을 테스트의 결과가 포함할 수 있습니다. 

class TimeoutTest : public ::testing::Test {
protected:
	time_t startTime;
	static const int PIVOT_SECONDS = 2;

	virtual void SetUp() {
		startTime = time(0);
	}

	virtual void TearDown() {
		time_t endTime = time(0);
		time_t duration = endTime - startTime;

		EXPECT_TRUE(duration < PIVOT_SECONDS) << "Timeout: " << duration;
	}
};

void foo()
{
	sleep(3);
}

// 아래의 테스트는 반드시 2초 안에 수행되어야 합니다.
TEST_F(TimeoutTest, sample)
{
	// SetUp
	foo();
	// TearDown
}




