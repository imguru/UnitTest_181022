
// 테스트 대역 용도 1. 특수한 상황을 시뮬레이션 할 수 있다.
//  => Stub
//   : SUT가 의존하는 객체의 동작을 검증목적으로 하나의 동작만
//     수행하도록 한다.

#include <stdio.h>

struct IConnection {
	virtual void move(int x, int y) = 0;
	virtual void attack() = 0;

	virtual ~IConnection() {}
};

class TCPConnection : public IConnection {
public:
	virtual void move(int x, int y) { 
		// ...
	}

	virtual void attack() {
		// ...
	}
};

class User {
	IConnection* conn;
public:
	User(IConnection* p = nullptr) : conn(p) {
		if (conn == nullptr)
			conn = new TCPConnection;
	}


	void move(int x, int y) { 
		try {
			conn->move(x, y);
		} catch (IOException e) {
			// SUT 
		}
	}

	void attack() {
		conn->attack();
		// SUT
	}
};

#include <iostream>
struct IOException : std::exception {};
#include "gtest/gtest.h"

// 연결이 끊어진 케이스를 구현하는 테스트 더블 - Stub
class BadConnection : public IConnection {
public:
	virtual void move(int x, int y) override {
		throw IOException();
	}

	virtual void attack() override {
		throw IOException();
	}
};

class UserTest : public ::testing::Test {
protected:
	User* user;
	BadConnection stub;

	virtual void SetUp() override {
		user = new User(&stub);
	}

	virtual void TearDown() override {
		delete user;
	}
};

// 인터넷이 안돼는 상황에서, move를 수행할 경우, IOException 예외가
// 발생하는 지 여부를 검증하고 싶다.
TEST_F(UserTest, moveTest) 
{
	ASSERT_THROW(user->move(10, 32), IOException);
}

TEST_F(UserTest, attackTest) 
{
	ASSERT_THROW(user->attack(), IOException);
}









