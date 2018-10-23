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

class CarTest : public ::testing::Test {};

TEST_F(CarTest, startTest)
{
	Engine* engine = new Engine;
	Car* car = new Car(engine);

	car.start();

	// 검증할 상태가 존재하지 않습니다.

}
















