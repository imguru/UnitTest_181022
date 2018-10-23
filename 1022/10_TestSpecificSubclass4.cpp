#include <stdio.h>

#include "gtest/gtest.h"

// pImpl Idioms 설계를 도입하면 아래의 방법을 사용할 수 없습니다.
// http://ozt88.tistory.com/32  - 참고 
#define class struct
#define private public
#include "User.h"

TEST(UserTest, levelTest)
{
	User user;
	ASSERT_EQ(42, user.level);
}

#if 0
int main() {
	User user;
	printf("%d\n", user.level);
}
#endif
