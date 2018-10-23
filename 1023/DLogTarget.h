#ifndef DLogTarget_H
#define DLogTarget_H
#include <string>

struct DLogTarget {
	virtual void write(Level level, const string& message) = 0;

	virtual void move(int x, int y) = 0;
	virtual void attack() = 0;
	virtual std::string getName() const = 0;

	virtual ~DLogTarget() {}
};

#endif
