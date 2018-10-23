#include "gtest/gtest.h"

// Google mock 설치 방법.
//  1. 파일을 하나로 합치는 스크립트 실행.
//   $ ../googletest/googlemock/scripts/fuse_gmock_files.py gtest
//   $ cd gtest
//  2. gmock.a 생성
//   $ g++ gmock-gtest-all.cc -c -I.
//   $ ar rcv gmock.a gmock-gtest-all.o
//  3. gmock_main.a 생성
//   $ cp ../../googletest/googlemock/src/gmock_main.cc .
//   $ g++ gmock_main.cc -I. -c
//   $ ar rcv gmock_main.a gmock-gtest-all.o gmock_main.o
//	
//	4. 소스 빌드
//	 $ cd ..
//   $ g++ sample.cpp ./gtest/gmock_main.a -Igtest -lpthread

TEST(SampleTest, foo) {}
