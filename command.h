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

	inline bool getCompleted() {  return bCompleted; }
	inline void setCompleted() { this->bCompleted = true; };
	inline bool getStarted() { return this->bStarted; }
	inline void setStarted() { this->bStarted = true; }

	virtual void Update() {};

};

// <------------------------------- Talk Command ------------------------------->
class cCommand_Talk : public cCommand {
public:
	cCommand_Talk(string textToDisplay, int framesDuration);
	cCommand_Talk(string character, string textToDisplay, int iMsDuration);
	~cCommand_Talk();


	void Update() override;

private:
	int iFramesDuration;
	string textToDisplay;
};

// <------------------------------- Move Command ------------------------------->
class cCommand_MoveTo : public cCommand {
public:
	cCommand_MoveTo(Dynamic* dynamic, float x, float y);
	~cCommand_MoveTo();

	void Update() override;

private:
	Dynamic* dynamic;
	float m_fStartPosX;
	float m_fStartPosY;
	float m_fTargetPosX;
	float m_fTargetPosY;
};