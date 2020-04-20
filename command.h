#pragma once
#include "dynamic.h"
#include "textDrawer.h"

class cCommand {
protected:
	bool bCompleted = false;
	bool bStarted = false;

public:
	cCommand();
	virtual ~cCommand();

	inline bool isCompleted() {  return bCompleted; }
	inline bool getStarted() { return this->bStarted; }
	inline void setStarted() { this->bStarted = true; }

	virtual void Start() {};
	virtual void Update(int iElapsedTime) {};

};

// <------------------------------- Talk Command ------------------------------->
class cCommand_Talk : public cCommand {
public:
	cCommand_Talk(string textToDisplay, int iMsDuration);
	cCommand_Talk(string character, string textToDisplay, int iMsDuration);
	~cCommand_Talk();

	inline void finish() { this->bCompleted = true; };
	void Start() override;
	void Update(int msElapsed) override;

private:
	int iMsDisplaying;
	int iMsDuration;
	string textToDisplay;
};

// <------------------------------- Move Command ------------------------------->
class cCommand_MoveTo : public cCommand {
public:
	cCommand_MoveTo(Dynamic* dynamic, float x, float y);
	~cCommand_MoveTo();
	void Start() override;
	void Update(int iElapsedTime) override;

private:
	Dynamic* dynamic;
	float m_fStartPosX;
	float m_fStartPosY;
	float m_fTargetPosX;
	float m_fTargetPosY;
};