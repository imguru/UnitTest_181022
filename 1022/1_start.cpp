// Google Test를 설치하고 빌드하는 방법
// 1. google test 소스를 다운로드 받는다.
// 2. 압축을 해지한다.
//   $ tar xvf release.tar.gz
// 3. 1) 제품 코드(SUT)
//    2) 구글 테스트 
//    3) 구글 테스트를 이용해서 만든 단위 테스트 프로그램

// googletest/scripts/fuse_gtest_files.py 스크립트를 이용하면, 파일을
// 두개의 파일로 합칠 수 있습니다.
//   $ ./fuse_gtest_files.py out
//   $ mv out/gtest ~/project
//   $ cd ~/project

//   $ cd gtest
//   $ g++ gtest-all.cc -c -I../
//   $ ar rcv gtest.a gtest-all.o
//   $ cd ..

//   $ g++ 1_start.cpp ./gtest/gtest.a -I. -lpthread 
//   $ ./a.out
//   : google test는 제품의 코드가 변경될 때마다, 매번 새로운 빌드를
//     수행해서 테스트 프로그램을 만드는 것이 좋습니다. 
//      => 정적 라이브러리를 사용하는 것을 권장합니다.
//      $ g++ gtest_main.cc -c -I../
//      $ ar rcv gtest_main.o gtest-all.o^C

#include "gtest/gtest.h"
#include <stdio.h>

// 용어(xUnit 표준)
//  TestCase class
//    - TestCase(TC)
//
// Google Test 용어
// 	TestCase
// 	  - Test

// TestCase 클래스를 만들지 않고, 바로 테스트를 만드는 방법
TEST(SampleTest, firstTest)
{
	printf("SampleTest.firstTest 수행되었음.\n");
	// 작성 중인 테스트는 반드시 실패해야 합니다. 
	

	// 테스트를 명시적으로 실패하는 방법.
	//  => 실패의 원인을 반드시 명시해야 한다.
	FAIL() << "작성 중입니다.";
}

#if 0
int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
#endif















