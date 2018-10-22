class Calculator {
public:
	double display() { return 0; }

	void enter(double value) {}
	void pressPlus() {}
	void pressMinus() {}
	void pressEqual() {}

	void calculate() {}
};
#include "gtest/gtest.h"

// 픽스쳐 설치 방법 2. 위임 설치
//  1. 동일한 픽스쳐를 가진 테스트 함수를 클래스로 묶는다.
//  2. 픽스쳐 설치에 관해 중복되는 코드를 함수로 제공한다.

// 테스트 케이스 클래스를 만드는 방법
// "테스트 케이스 클래스": 동일한 픽스쳐를 가지는 테스트의 집합
class CalculatorTest : public ::testing::Test {
	// private로 하면 테스트 함수에서 접근이 불가능합니다.
protected:
	// Test Utility Method
	//  : creation method
	//  테스트를 작성하면서, 코드의 중복이 발생하면, 반드시
	//  별도의 함수를 통해서 관리하는 것이 좋습니다. 
	Calculator* create() {
		return new Calculator;
	}
};

TEST_F(CalculatorTest, addTest)
{
	Calculator* calc = create();

	calc->enter(2);
	calc->pressPlus();
	calc->enter(2);
	calc->pressEqual();

	ASSERT_EQ(4, calc->display());
}

TEST_F(CalculatorTest, minusTest)
{
	Calculator* calc = create();

	calc->enter(2);
	calc->pressMinus();
	calc->enter(2);
	calc->pressEqual();

	ASSERT_EQ(0, calc->display());
}


