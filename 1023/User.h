struct User {
	virtual void stop() = 0;
	virtual void move(int x, int y) = 0;
	virtual int getX() const = 0;
	virtual int getY() const = 0;

	virtual ~User() {}
};
