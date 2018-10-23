#include <stdio.h>

class User {
public:
	User() : level(42) {}
protected:
	int level;
	int getLevel() { return level; }
};

class TestUser : public User {
public:
	using User::level;
	// 부모의 protected -> public 변경한다.
};

int main() {
	TestUser user;
	printf("%d\n", user.level);
}
