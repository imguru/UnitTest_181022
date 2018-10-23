
// DLog target
//   File        -> write
//   Cloudwatch  -> write
#include <stdio.h>
#include <vector>
#include <string>
using namespace std;

enum Level {
	DEBUG, INFO, WARN, ERROR, CRITICAL
};

struct DLogTarget {
	virtual void write(Level level, const string& message) = 0;

	virtual ~DLogTarget() {}
};


class DLog {
	vector<DLogTarget*> targets;
public:
	void addTarget(DLogTarget* p) {
		targets.push_back(p);
	}
	
	void write(Level level, const string& message) {
		for (DLogTarget* e: targets) {
			e->write(level, message);
		}
	}
};

#include "gtest/gtest.h"
#include <algorithm>

// 함수를 호출하였을 때, 관찰할 수 있는 부수효과가 없어서
// 테스트 안된 요구사항이 있다.
//   => Test Spy
//
//  Spy: 목격한 일을 기록해두었다가, 나중에 테스트에서 확인할 수 있도록
//       만들어진 테스트 대역
//   => 다른 컴퓨넌트로부터의 간접 출력을 저장해 두었다가, 검증한다.

class SpyTarget : public DLogTarget {
	vector<string> history;

	string concat(Level level, const string& message) {
		static int levels[] = {
			10, 20, 30, 40, 50
		};

		return to_string(levels[level]) + "@" + message;
	}

public:
	virtual void write(Level level, const string& message) override {
		history.push_back(concat(level, message));
	}

	bool received(Level level, const string& message) {
		const string log = concat(level, message);
		return find(history.begin(), history.end(), log) != history.end();
	}
};

class DLogTest : public ::testing::Test {
protected:
};

TEST_F(DLogTest, writeTest) 
{
	SpyTarget spy1, spy2;
	DLog logger;
	logger.addTarget(&spy1);
	logger.addTarget(&spy2);

	logger.write(INFO, "test_logging_message");

	EXPECT_TRUE(spy1.received(INFO, "test_logging_message"));
	EXPECT_TRUE(spy2.received(INFO, "test_logging_message"));
}








