#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

struct User {
	virtual void stop() = 0;
	virtual void move(int x, int y) = 0;
	virtual int getX() const = 0;
	virtual int getY() const = 0;

	virtual ~User() {}
};

// Mocking
class MockUser : public User {
 public:
  MOCK_METHOD0(stop,
      void());
  MOCK_METHOD2(move,
      void(int x, int y));
  MOCK_CONST_METHOD0(getX,
      int());
  MOCK_CONST_METHOD0(getY,
      int());
};

// 행위 기반 검증 
// 1. 호출 여부 검증 - EXPECT_CALL
// 2. 호출 횟수 검증
// 3. 호출 순서 검증  

void foo(User* user)  {
	user->move(10, 32);
}

TEST(MockTest, example1) {
	// 1. Arrange - Mock 생성
	MockUser mock;
	// MockUser* user = new MockUser;
	// : 검증 시점은 목 객체가 파괴되는 시점입니다.

	// 2. 기대행위를 명시한다.
	EXPECT_CALL(mock, move(10, 32));

	// 3. mock을 실제 테스트 하는 객체 또는 함수에 주입한다.
	foo(&mock);
}

void goo(User* user) {
	user->stop();
	user->stop();
}

// AnyNumber
using ::testing::AnyNumber;
TEST(MockTest, gooTest) {
	MockUser mock;

	// EXPECT_CALL(mock, stop());  // 1번 호출!
	// EXPECT_CALL(mock, stop()).Times(2);  
	EXPECT_CALL(mock, stop()).Times(AnyNumber());   // 1번 이상!

	goo(&mock);
}

void hoo(User* user) {
	user->move(1, 20);
	user->stop();
}

// 인자를 모를 경우 사용하면 됩니다. -> _
// InSequence
using ::testing::_;
using ::testing::InSequence;
TEST(MockTest, hooTest) {
	MockUser mock;
	InSequence seq; // !!

	EXPECT_CALL(mock, move(_, 20));
	EXPECT_CALL(mock, stop());

	hoo(&mock);
}

#include <iostream>
using namespace std;

// Google Mock - Stub도 만들 수 있습니다.
class Time {
public:
	string getCurrentTimeString() { return "16:24"; }
};

// MockTime
class MockTime : public Time {
public:
	MOCK_METHOD0(getCurrentTimeString, string());
};

using ::testing::Return;
TEST(StubTest, foo) {
	MockTime stub;
	ON_CALL(stub, getCurrentTimeString()).WillByDefault(Return("00:00"));

	cout << stub.getCurrentTimeString() << endl;
}







































