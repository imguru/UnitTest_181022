#include <unistd.h>
#include <stdio.h>
#include <string>
using namespace std;

// SUT
class Terminal {
public:
	void connect()
	{
		// 2초
		sleep(2);
	}

	void disconnect()
	{
		// 2초 
		sleep(2);
	}

	void login(const string& id, const string& password) {}
	void logout() {}
	bool isLogin() { return true; }
};

//------------------------------------------------
#include "gtest/gtest.h"

#if 1
// 픽스쳐 설치 / 해체 작업이 느린 작업인 경우, 테스트 함수를 추가할 때마다
// 전체적인 테스트의 시간이 계속 느려지는 문제가 발생한다.
// => Slow Test Problem
//  : 테스트가 너무 느려서, 개발자들이 SUT가 변경되어도 테스트를
//    수행하지 않는다.
//    (테스트를 수행하는 개발자의 생산성을 떨어뜨린다.)

class TerminalTest : public ::testing::Test
{
protected:
	static const string ID;
	static const string PASSWORD;

	Terminal* term;

	// @Override
	virtual void SetUp() override 
	{
		term = new Terminal;
		term->connect();
	}

	virtual void TearDown() override
	{	
		term->disconnect();
		delete term;
	}
};

const string TerminalTest::ID = "test_id";
const string TerminalTest::PASSWORD = "test_password";

TEST_F(TerminalTest, loginTest)
{
	term->login(ID, PASSWORD);

	ASSERT_TRUE(term->isLogin());
}

TEST_F(TerminalTest, logoutTest)
{
	term->login(ID, PASSWORD);
	term->logout();

	ASSERT_FALSE(term->isLogin());
}
#endif
#if 0
class TerminalTest : public ::testing::Test
{
protected:
};

TEST_F(TerminalTest, loginTest)
{
	string id = "test_id";
	string password = "test_password";
	Terminal* term = new Terminal;
	term->connect();

	term->login(id, password);

	ASSERT_TRUE(term->isLogin());

	term->disconnect();
	delete term;
}

TEST_F(TerminalTest, logoutTest)
{
	string id = "test_id";
	string password = "test_password";
	Terminal* term = new Terminal;
	term->connect();

	term->login(id, password);
	term->logout();

	ASSERT_FALSE(term->isLogin());

	term->disconnect();
	delete term;
}
#endif
