#pragma once

class Timer {
public:
	Timer();
	~Timer();
	inline int getMsSinceStart() { return this->msSinceStart;}
	void resetTime();
	inline int getMsSinceLastFrame() { return this->msSinceLastFrame;}
	void updateTimer();
private:
	int msSinceStart;
	int msSinceLastFrame;
	unsigned long  timeSinceEpoch;
};