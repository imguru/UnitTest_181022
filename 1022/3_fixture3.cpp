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

// 방법 3. 암묵적 설치 / 해체 
//  => xUnit Test Framework 에서 제공하는 기능.
//    SetUp() / TearDown()
//     : 각각의 테스트를 수행하기 전에 수행되는 함수.
//  장점: 테스트 코드 중복을 제거하고, 꼭 필요하지 않은
//        상호작용을 캡슐화할 수 있다. 
//  단점: 픽스쳐 설치 코드가 함수 밖에 존재하기 때문에,
//        테스트 함수 만으로 코드를 이해하기 어렵다.

// Test Framework의 테스트 수행 흐름
//  => 신선한 픽스쳐 전략
// CalculatorTest* testcase = new CalculatorTest();
// testcase->SetUp();
// testcase->addTest();
// testcase->TearDown();
// delete testcase;
//
// CalculatorTest* testcase = new CalculatorTest();
// testcase->SetUp();
// testcase->minusTest();
// testcase->TearDown();
// delete testcase;

// xUnit Test Framework에서는 4단계 테스트 패턴을 이용합니다.
// 1단계: 테스트의 픽스쳐를 설치하거나, 실제 결과를 관찰하기 위해
//        필요한 것을 집어넣는다.
// 2단계: SUT와 상호 작용한다.
// 3단계: 기대 결과를 확인한다.
// 4단계: 테스트 픽스쳐를 해체해서, 테스트 시작 이전의 상태로 돌려놓는다. 
//
// 단위 테스트 품질 기준 3가지
// 1. 가독성
// 2. 유지보수성 
// 3. 신뢰성 

class CalculatorTest : public ::testing::Test {
public:
	~CalculatorTest()
	{
		printf("~CalculatorTest()\n");
	}

	CalculatorTest() 
	{
		printf("CalculatorTest()\n");
	}
protected:
	virtual void SetUp() {
		printf("SetUp()\n");
		calc = new Calculator();
	}

	virtual void TearDown() {
		printf("TearDown()\n");
		delete calc;
	}
	
	Calculator* calc;
};

TEST_F(CalculatorTest, addTest)
{
	printf("  addTest\n");
	calc->enter(2);
	calc->pressPlus();
	calc->enter(2);
	calc->pressEqual();

	ASSERT_EQ(4, calc->display());
}

TEST_F(CalculatorTest, minusTest)
{
	printf("  minusTest\n");
	calc->enter(2);
	calc->pressMinus();
	calc->enter(2);
	calc->pressEqual();

	ASSERT_EQ(0, calc->display());
}
