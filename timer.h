#pragma once

class Timer {
public:
	Timer();
	~Timer();
	inline int getMsSinceStart() { return this->msSinceStart;}
	void updateTimer();

private:
	int msSinceStart;
	unsigned long  msStart;
};