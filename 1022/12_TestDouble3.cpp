#include <stdio.h>
#include <string>
using namespace std;

// C++ Interface
struct IFileSystem {
	virtual bool isValid(const string& name) = 0;
	virtual ~IFileSystem() {}
};

class FileSystem : public IFileSystem {
public:
	bool isValid(const string& filename) {
		// ...
		return false;
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

// 의존하는 객체를 테스트 대역으로 교체해야 합니다.
// => 항상 동일한 결과를 반환하는 간단한 테스트 대역(Stub)
class StubFileSystem : public IFileSystem {
public:
	virtual bool isValid(const string& filename) {
		return true;
	}
};


TEST_F(LoggerTest, isValidFilename_NameShorterThan5Chars_ReturnsFalse) {
	StubFileSystem stub;
	Logger logger(&stub);
	string filename = "bad.log";

	bool actual = logger.isValidFilename(filename);

	ASSERT_FALSE(actual) << "파일명이 다섯글자 미만일 때";
}

TEST_F(LoggerTest, isValidFilename_NameLoggerThan5Chars_ReturnsTrue) {
	StubFileSystem stub;
	Logger logger(&stub);
	string filename = "good_file.log";

	bool actual = logger.isValidFilename(filename);

	ASSERT_TRUE(actual) << "파일명이 다섯글자 이상일 때";
}





























