// Mock Object(모의 객체)
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
#include "gmock/gmock.h"   // !!

// DLog에 대해서 write 호출시, 등록된 모의 객체에 대해서 write가
// 동일 인자로 호출되어야 한다.
class DLogTest : public ::testing::Test {};

// Mocking
#if 0
struct DLogTarget {
	virtual void write(Level level, const string& message) = 0;

	virtual ~DLogTarget() {}
};

#endif

// 아래의 코드는 직접 생성하는 것이 아니라, gmock이 제공하는 스크립트를 
// 이용하면 편리합니다.
// $ ../googletest/googlemock/scripts/generator/gmock_gen.py DLogTarget.h
class MockTarget : public DLogTarget {
public:
	// MOCK_METHOD{인자 개수}(함수 이름, 함수 타입);
	
	MOCK_METHOD2(write, void(Level, const string&));
};

TEST_F(DLogTest, writeTest) 
{
	// Arrange
	MockTarget mock1, mock2;
	DLog logger;
	logger.addTarget(&mock1);
	logger.addTarget(&mock2);

	// 행위 기반 검증 요소를 설정 - Assert
	EXPECT_CALL(mock1, write(INFO, "test_message"));
	EXPECT_CALL(mock2, write(INFO, "test_message"));

	// Act
	logger.write(INFO, "test_message");
}

// 테스트 대역 목적
//  목적: 격리 => 원하는 부분을 검증 한다.
//    => 결함 국소화!
// 1) Stub
//   : 비결정적 요소를 제어한다.(시간, 네트워크, 파일 시스템)
//     특수한 상황을 시뮬레이션 한다.
// 2) Fake
//   : 만들어지지 않은 모듈에 의존하는 객체를 검증하고자 할 때
//     의존하는 객체가 너무 느릴 때
// 3) Spy
//   : 숨겨진 정보를 확인하는 용도(상태 기반 검증)
// 4) Mock
//   : 행위 기반 검증(Google Mock Framework)
//
// => 테스트 대역을 적용할 수 있는 설계가 반드시 전제되어야 한다.
//    : 의존성 주입!
