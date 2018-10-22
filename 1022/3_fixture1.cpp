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

// Fixture
// 정의: xUnit Test Pattern에서는 SUT를 실행하기 위해 준비해야 하는
//       모든 것을 테스트 픽스쳐라고 합니다.
//     - 픽스쳐를 구성하는 모든 로직 부분을 '픽스쳐를 설치한다.'
//       라고 합니다.

// 1. 인라인 픽스쳐 설치
// : 모든 픽스쳐 설치에 관련된 코드를 테스트 함수 안에서 처리한다.
// 장점: 픽스쳐 설치와 검증 로직이 테스트 함수안에서 존재하기 때문에
//      인과 관계를 쉽게 파악할 수 있다. 
// 단점: 모든 테스트 함수 안에서 '코드 중복'이 발생합니다. 
//
// 테스트 냄새
//  : 테스트의 유지보수성을 떨어뜨린다.
TEST(CalculatorTest, addTest)
{
	Calculator* calc = new Calculator;

	calc->enter(2);
	calc->pressPlus();
	calc->enter(2);
	calc->pressEqual();

	ASSERT_EQ(4, calc->display());
}

TEST(CalculatorTest, minusTest)
{
	Calculator* calc = new Calculator;

	calc->enter(2);
	calc->pressMinus();
	calc->enter(2);
	calc->pressEqual();

	ASSERT_EQ(0, calc->display());
}


