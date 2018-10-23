#include <stdio.h>
#include <string>
using namespace std;

class User {
	string id_;
	int level_;
	int gold_;
public:
	User(string id, int level, int gold)
		: id_(id), level_(level), gold_(gold) {}

	string id() const { return id_;    }
	int level() const { return level_; }
	int gold() const  { return gold_;  }
};

struct IDatabase {
	virtual void save(string id, User* user) = 0;
	virtual User* load(string id) = 0;

	virtual ~IDatabase() {}
};

class UserManager {
	IDatabase* database;
public:
	UserManager(IDatabase* p) : database(p) {}

	void save(User* user) {
		database->save(user->id(), user);
	}

	User* load(string id) {
		return database->load(id);
	}
};

// UserManager Unit test
//
// 테스트 대역 목적 
// 2. 아직 준비되지 않은 의존 객체로 인해 테스트 할 수 없는 경우
//  => Fake Object Pattern
//  1) 의존 객체를 사용할 수 없을 때, 해당 로직을 독립적으로 검증가능하다.
//  2) 의존 객체가 너무 느려서, 느린 테스트 문제가 발생할 때
//
//  : 의존하는 객체를 훨씬 가볍고 빠르게 동작하는 것으로 교체한다.
//  => Stub 으로는 문제를 해결할 수 없는 경우
#include "gtest/gtest.h"
#include <map>
using namespace std;

class MemoryDatabase : public IDatabase {
	map<string, User*> data;
public:
	virtual void save(string id, User* u) override {
		data[id] = u;
	}

	virtual User* load(string id) override {
		return data[id];
	}
};

class UserManagerTest : public ::testing::Test {

};

// 사용자 정의 타입을 위한 연산자 재정의 함수를 제공해야 합니다.
bool operator==(const User& lhs, const User& rhs) {
	return lhs.id() == rhs.id() &&
		lhs.level() == rhs.level() &&
		lhs.gold() == rhs.gold();
}

TEST_F(UserManagerTest, saveTest)
{
	MemoryDatabase fake;
	UserManager manager(&fake);
	string test_id = "test_id";
	int test_level = 10;
	int test_gold = 1000;

	User user(test_id, test_level, test_gold);
	manager.save(&user);
	User* actual = manager.load(test_id);

	ASSERT_NE(nullptr, actual);
	ASSERT_EQ(user, *actual);
	// 사용자 정의 타입에 대해서,
	// EQ(==) 를 사용하기 위해서는,
	// 연산자 재정의가 필요합니다.
}









