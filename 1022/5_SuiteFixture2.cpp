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

#if 0
TerminalTest::SetUpTestCase();
TerminalTest()
terminalTest->SetUp();
terminalTest->loginTest();
terminalTest->TearDown();
~TerminalTest()

TerminalTest()
terminalTest->SetUp();
terminalTest->logoutTest();
terminalTest->TearDown();
~TerminalTest()
TerminalTest::TearDownTestCase();
#endif

// 문제점?
//  : 신선한 픽스쳐 전략 -> 공유 픽스쳐 전략으로 변경된다.
//    모든 테스트가 더 이상 독립적이지 않다.
//    => 잘못된 테스트가 이후 테스트에 영향을 미칠 수 있다.  
//     : [변덕 스러운 테스트]의 문제가 발생할 수 있다.
//      "공유 픽스쳐의 상태에 따라서 테스트의 결과가 변한다."
//
// 1. 가독성
// 2. 유지보수성
// 3. 신뢰성

class TerminalTest : public ::testing::Test
{
protected:
	static const string ID;
	static const string PASSWORD;

	static Terminal* term;

	static void SetUpTestCase()
	{
		printf("SetUpTestCase()\n");
		term = new Terminal;
		term->connect();
	}

	static void TearDownTestCase()
	{
		printf("TearDownTestCase()\n");
		term->disconnect();
		delete term;
	}

	// @Override
	virtual void SetUp() override 
	{
		printf("SetUp()\n");
	}

	virtual void TearDown() override
	{	
		printf("TearDown()\n");
	}
};

const string TerminalTest::ID = "test_id";
const string TerminalTest::PASSWORD = "test_password";
Terminal* TerminalTest::term = nullptr;

TEST_F(TerminalTest, loginTest)
{
	printf("  loginTest()\n");
	term->login(ID, PASSWORD);

	ASSERT_TRUE(term->isLogin());
}

TEST_F(TerminalTest, logoutTest)
{
	printf("  logoutTest()\n");
	term->login(ID, PASSWORD);
	term->logout();

	ASSERT_FALSE(term->isLogin());
}

TEST_F(TerminalTest, foo) {}
TEST_F(TerminalTest, goo) {}

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
