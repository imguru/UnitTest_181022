// Test Double Pattern
//  : xUnit Test Pattern의 가장 중요한 패턴
// 종류
//  1. Test Stub
//  2. Fake Object
//  3. Test Spy
//  4. Mock Object
//
// 목적
//  : SUT를 격리해서 테스트 환경을 통제하는 것이 목적이다.
// 한계
//  : 테스트 대역을 적용할 수 있는 설계가 반드시 필요합니다.

#include <stdio.h>
#include <string>
using namespace std;

// 외부 의존물에 의해 테스트의 결과가 좌우 되면 안된다.
class FileSystem {
public:
	bool isValid(const string& filename) {
		// ...
		return true;
	}
};

class Logger {
public:
	// 파일의 이름이 반드시 5글자 이상.
	// file.log
	//   확장자를 제외한 file 이름이 다섯글자 이상
	bool isValidFilename(const string& filename) {
		//------------------
		size_t index = filename.find_last_of(".");
		string name = filename.substr(0, index);

		if (name.size() < 5) 
			return false;
		//-----------------

		FileSystem* fs = new FileSystem;
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





























