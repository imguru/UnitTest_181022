#include "gtest/gtest.h"

#define MEMORY_LEAK_TEST
#include "Image.h"

class ImageTest : public ::testing::Test {
protected:
	int allocCount = 0;

	virtual void SetUp() override {
		allocCount = Image::allocObjectCount;
	}

	virtual void TearDown() override {
		int diff = Image::allocObjectCount - allocCount;
		EXPECT_EQ(0, diff) << "Memory Leaks - " << diff << " objects";
	}
};

void foo()
{
	for (int i = 0 ; i < 10 ; ++i)
		Image* p = new Image;
}

TEST_F(ImageTest, sample)
{
	foo();
}













