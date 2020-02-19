#pragma once
#include "dynamic.h"

class cCommand {
protected:
	bool bCompleted = false;
	bool bStarted = false;

public:
	cCommand() {};
	virtual ~cCommand() {};

	inline bool isCompleted() { return bCompleted; }
	inline bool getStarted() { return this->bStarted; }
	inline void setStarted() { this->bStarted = true; }

	virtual void Start() {};
	virtual void Update(int iElapsedTime) {};

};