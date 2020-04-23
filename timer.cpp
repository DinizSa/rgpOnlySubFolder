#include "timer.h"
#include <ctime>
#include <iostream>
#include <chrono>
using namespace std;
#include <iostream>

Timer::Timer(){
	timeSinceEpoch = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
	msSinceStart = 0;
	msSinceLastFrame = 0;
}

Timer::~Timer(){

}

void Timer::resetTime() {
	msSinceStart = 0;
	msSinceLastFrame = 0;
	timeSinceEpoch = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
}

void Timer::updateTimer() {
	int msSinceStartLast = msSinceStart;
	msSinceStart = (std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1)) - timeSinceEpoch;
	msSinceLastFrame = msSinceStart - msSinceStartLast;
}