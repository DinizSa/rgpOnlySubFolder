#pragma once

class Timer {
public:
	Timer();
	~Timer();
	inline int getMsSinceStart() { return this->msSinceStart;}
	inline int getMsSinceLastFrame() { return this->msSinceLastFrame;}
	void updateTimer();
private:
	int msSinceStart;
	int msSinceLastFrame;
	unsigned long  msStart;
};