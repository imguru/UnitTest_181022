#include "gtest/gtest.h"
#include <time.h>

class TimeoutTest : public ::testing::Test {
protected:
	time_t startTime;
	int pivotSeconds;
	
	void setPivotSeconds(int n) { pivotSeconds = n; }

	virtual void SetUp() {
		startTime = time(0);
	}

	virtual void TearDown() {
		time_t endTime = time(0);
		time_t duration = endTime - startTime;

		EXPECT_TRUE(duration < pivotSeconds) << "Timeout: " << duration;
	}
};

void foo() { sleep(2); }

TEST_F(TimeoutTest, sample1)
{
	setPivotSeconds(1);

	foo();
}

TEST_F(TimeoutTest, sample2)
{
	setPivotSeconds(3);

	foo();
}
