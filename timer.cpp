#include "timer.h"
#include <ctime>
#include <iostream>
#include <chrono>

Timer::Timer(){
	msStart = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
	msSinceStart = 0;
}

Timer::~Timer(){

}

void Timer::updateTimer() {
	msSinceStart = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
}