#pragma once
#include "commands.h"

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