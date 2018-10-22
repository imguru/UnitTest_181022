// 2_3A.cpp
// 단위 테스트를 구성하는 방법

// SUT
class Calculator {
public:
	double display() { return 0; }

	void enter(double value) {}
	void pressPlus() {}
	void pressMinus() {}
	void pressEqual() {}

	void calculate() {}
};

//----------------------------------
// 단위 테스트는 '3A'에 의해서 테스트를 구성합니다.
// 1. 객체를 생성하고, 필요한 경우에 적절하게 설정하고 준비한다.
//  -> Arrange
// 2. 객체에 작용을 가한다.
//  -> Act
// 3. 기대하는 바를 단언한다.
//  -> Assert
//
// 3A(TDD) / BDD
//  1. Given
//  2. When
//  3. Then
#include "gtest/gtest.h"

// 테스트의 이름은 테스트의 시나리오가 드러날 수 있도록 해야 한다.
//  : 테스트대상메소드_시나리오_기대값
// TEST(CalculatorTest, test1)
// => junit 5는 테스트 이름을 한글로 지을 수 있는 기능을 제공한다.
TEST(CalculatorTest, display_addingTwoPlusTwo_DisplaysFour)
{
	// Arrange
	Calculator* calc = new Calculator();

	// Act
	calc->enter(2);
	calc->pressPlus();
	calc->enter(2);
	calc->pressEqual();

	// Assert
	//  테스트 함수 안에서는 절대 반복문이나 조건문같은 제어 구문이
	//  발생하면 안됩니다. 
	//  1. 테스트 함수는 별도의 검증이 불가능하다.
	//  2. xUnit Test Framework은 검증을 위한 다양한 매크로를 제공하고
	//     있습니다. - 단언 매크로
	//  3. 실패의 이유를 명확하게 표현해야 합니다. 
	// ASSERT_EQ(calc->display(), 4);
	// 주의점: 인자의 순서가 중요합니다.
	//    ASSERT_EQ(expected-값, actual-값)
	ASSERT_EQ(4, calc->display()) << "when adding 2 + 2";

	#if 0
	if (calc->display() != 4)
		FAIL();
	else
		SUCCEED();
	#endif
}




















