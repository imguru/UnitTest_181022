#include <stdio.h>
#include <string>
using namespace std;

// 아래의 SUT는 테스트 대역을 적용할 수 없는 설계입니다.
// * 틈새 만들기(seam): 테스트 대역을 적용할 수 있도록 변경하는 리팩토링
//   틈새: 테스트 대역 등의 다양한 기능을 SUT에 삽입할 수 있는 위치
//
// * 틈새 만들기
//  : 의존하는 객체를 교체 가능하도록 하는 유연한 설계(느슨한 결합)
//  => 구체적인 타입에 의존하는 것이 아니라, 인터페이스나 추상 클래스에 의존해야
//     한다. 
//     DIP(Dependency Inversion Principle)
//  1) Interface 
//  2) 절대 의존하는 객체를 직접 생성하면 안됩니다.
//     외부에서 생성해서 전달받아야 합니다.
//     => DI(Dependency Injection)
//
//  3) 의존성 주입
//    1) 생성자 주입
//      : 의존하는 객체가 반드시 필요한 경우, 생성자 주입을 사용한다.
//    2) 메소드 주입
//      : 의존하는 객체가 특정 메소드를 동작할 때만 필요한 경우,
//        메소드 주입
//
//  Boilerplate: 반드시 필요하지만, 반복되는 코드
//  
//	A a = new A();
//	B b = new B();
//  C c = new C(a, b);
//    : 가난한 자의 의존성 주입.
//
//  DI에 대한 반복되는 코드를 효율적으로 관리하기 위한 프레임워크
//   => DI 프레임워크
//    Java: Dagger2

// C++ Interface
struct IFileSystem {
	virtual bool isValid(const string& name) = 0;
	virtual ~IFileSystem() {}
};

class FileSystem : public IFileSystem {
public:
	bool isValid(const string& filename) {
		// ...
		return true;
	}
};

class Logger {
	IFileSystem* fs;
public:
	// 기존의 사용법과 동일하게 만들어주는 것이 좋다.
	Logger(IFileSystem* p = nullptr) : fs(p) {
		if (fs == nullptr) {
			fs = new FileSystem;
		}
	}
	
	bool isValidFilename(const string& filename) {
		//------------------
		size_t index = filename.find_last_of(".");
		string name = filename.substr(0, index);

		if (name.size() < 5) 
			return false;
		//-----------------
		// IFileSystem* fs = new FileSystem;
		return fs->isValid(filename);
	}
};

#include "gtest/gtest.h"

class LoggerTest : public ::testing::Test {};

TEST_F(LoggerTest, isValidFilename_NameShorterThan5Chars_ReturnsFalse) {
	Logger logger;
	string filename = "bad.log";

	bool actual = logger.isValidFilename(filename);

	ASSERT_FALSE(actual) << "파일명이 다섯글자 미만일 때";
}

TEST_F(LoggerTest, isValidFilename_NameLoggerThan5Chars_ReturnsTrue) {
	Logger logger;
	string filename = "good_file.log";

	bool actual = logger.isValidFilename(filename);

	ASSERT_TRUE(actual) << "파일명이 다섯글자 이상일 때";
}





























