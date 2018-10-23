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
#include <algorithm>

// 함수를 호출하였을 때, 관찰할 수 있는 부수효과가 없어서
// 테스트 안된 요구사항이 있다.
//   => Test Spy
//   => Mock Object
//      행위 기반 검증 
//       : 함수의 반환값이 없거나, 반환값을 확인한 것 만으로는
//         예상했던 동작이 동작했음을 보장하기 어려울 때 사용한다. 
//     1. 함수 호출 여부
//     2. 함수 호출 횟수
//     3. 함수 호출 순서
//   -> 모의 객체는 직접 구현하는 것이 아니라 목 프레임워크를 이용합니다.
//   C++: Google Mock
//   Java: jMock, EasyMock, Mockito
//       => Spock Framework














