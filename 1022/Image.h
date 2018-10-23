#ifndef IMAGE_H
#define IMAGE_H
// SUT에 아래의 코드가 약속되어 있다면, 테스트에서 메모리 누수를 감지하는 기능을 이용할 수 있습니다. 

class Image {
public:
#ifdef MEMORY_LEAK_TEST
	static int allocObjectCount;
	
	void* operator new(size_t size) {
		++allocObjectCount;
		return malloc(size);
	}

	void operator delete(void* p, size_t) {
		--allocObjectCount;
		free(p);
	}

#endif

};

// Image.cpp
#ifdef MEMORY_LEAK_TEST
int Image::allocObjectCount = 0;
#endif

#endif
