
// 전역 픽스쳐(Global Fixture)
//  : google test에서는 전역(프로그램) 픽스쳐를 
//    설치/해체 할 수 있습니다. 

#include <stdio.h>
#include "gtest/gtest.h"

class MyTestEnvironment : public ::testing::Environment {
public:
	virtual void SetUp() override {
		printf("Global Fixture Setup()\n");
	}

	virtual void TearDown() override {
		printf("Global Fixture TearDown()\n");
	}
};

class SampleTest : public ::testing::Test {
protected:
	virtual void SetUp() override { printf("SetUp()\n"); }
	virtual void TearDown() override { printf("TearDown()\n"); }
};

TEST_F(SampleTest, foo) {}

class SampleTest2 : public ::testing::Test {
protected:
	virtual void SetUp() override { printf("SetUp()\n"); }
	virtual void TearDown() override { printf("TearDown()\n"); }
};

TEST_F(SampleTest2, foo) {}


#if 0
// 1. 전역 변수를 통해서 등록하는 방법
::testing::Environment* const env = 
	::testing::AddGlobalTestEnvironment(new MyTestEnvironment);
#endif


int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	// 2. main을 통해서 등록하는 방법
	::testing::AddGlobalTestEnvironment(new MyTestEnvironment);

	return RUN_ALL_TESTS();
}




























