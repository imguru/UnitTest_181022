// Google Test - Friend Test
#include "gtest/gtest.h"

class User {
private:
	int age;

public:
	User() : age(42) {}

	// 아래의 테스트 함수는 User의 private field / 함수에 접근이 가능합니다.
	FRIEND_TEST(UserTest, userTest);
};

class UserTest : public ::testing::Test {
};

TEST_F(UserTest, userTest) {
	User user;
	printf("age: %d\n", user.age);
}
