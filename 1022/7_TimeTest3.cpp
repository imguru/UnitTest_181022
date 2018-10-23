#include "gtest/gtest.h"
#include <time.h>

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
protected:
	//TimeoutTest 상속한 경우, 반드시 SetUp / TearDown 에서 부모의
	// SetUp / TearDown을 명시적으로 호출해야 합니다.
	virtual void SetUp() override {
		TimeoutTest::SetUp();

		printf("My SetUp()\n");
	}
	virtual void TearDown() override {
		TimeoutTest::TearDown();

		printf("My TearDown()\n");
	}
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

TEST_F(Timeout2Seconds, foo)
{
}

TEST_F(Timeout2Seconds, goo)
{
}

















