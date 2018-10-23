
#ifndef USER_H
#define USER_H
// User.h
class User {
	int level;
public:
	User() : level(42) {}
};
#if 0
class User {
public:
	User() : level(42) {}
private:
	int level;
};
#endif
#endif
