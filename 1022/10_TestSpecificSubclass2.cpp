#include <stdio.h>
// 10_테스트 전용 하위 클래스
// SUT
class Engine {
public:
	virtual void start() { printf("Engine started...\n"); }
};

class Car {
private:
	Engine* engine;
public:
	Car(Engine* e) : engine(e) {}

	void start() {
		engine->start();
		// ...
	}
};

//------------------------------------
#include "gtest/gtest.h"

// 21st Programming
//   C       -> Go -> (VM)
//   C++     -> Rust
//   Java    -> Kotlin

// Ubuntu: apt-get(C)
//         apt(Go)

//         grep
//         ag
//         ripgrep(rg) - rust
//


// 테스트 전용 하위 클래스(Test Specific Subclass Pattern)
//  의도: SUT의 private 상태나 관찰해야 하는 상태가 없는 경우,
//        어떻게 하면 테스트 가능하게 할 수  있는가?

// C++: 부모의 함수가 반드시 가상함수 이어야 한다.
// => 외부에서 호출되는 모든 기능은 가상적으로 동작해야 합니다.

// Subclass is BaseClass
class TestEngine : public Engine {
	bool isStart_;
public:
	TestEngine() : isStart_(false) {}

	bool isStart() { return isStart_; }
	virtual void start() override {
		Engine::start();

		isStart_ = true;
	}
};


class CarTest : public ::testing::Test {};

TEST_F(CarTest, startTest)
{
#if 0
	Engine* engine = new Engine;
#endif
	TestEngine* engine = new TestEngine;
	Car* car = new Car(engine);

	car->start();

	// 검증할 상태가 존재하지 않습니다.
	ASSERT_TRUE(engine->isStart());
}
















