#include "command.h"
#include "assets.h"

cCommand::cCommand(){
	bCompleted = false;
	bStarted = false;
}

cCommand::~cCommand() {};

// <------------------------------- Talk Command ------------------------------->
cCommand_Talk::cCommand_Talk(string textToDisplay, int framesDuration) {
	this->iFramesDuration = framesDuration;
	this->textToDisplay = textToDisplay;
	bCompleted = false;
	bStarted = false;
};
cCommand_Talk::cCommand_Talk(string name, string textToDisplay, int framesDuration) {
	this->iFramesDuration = framesDuration;
	this->textToDisplay = "[ " + name + " ]   " + textToDisplay;
	bCompleted = false;
	bStarted = false;
};

cCommand_Talk::~cCommand_Talk() {
};


void cCommand_Talk::Update() {
	bStarted = true;
	iFramesDuration--;
	cTextDrawer::get().setDialogue(textToDisplay);
	if (iFramesDuration < 0) {
		this->bCompleted = true;
		cTextDrawer::get().removeDialogue();
	}
};

// <------------------------------- Move Command ------------------------------->
cCommand_MoveTo::cCommand_MoveTo(Dynamic* dynamic, float x, float y) {
	this->dynamic = dynamic;
	this->m_fStartPosX = dynamic->getPosX();
	this->m_fStartPosY = dynamic->getPosY();
	m_fTargetPosX = x;
	m_fTargetPosY = y;
	bCompleted = false;
	bStarted = false;
}
cCommand_MoveTo::~cCommand_MoveTo() {

}


void cCommand_MoveTo::Update() {
	bStarted = true;
	float currentPosX = dynamic->getPosX();
	float currentPosY = dynamic->getPosY();
	float m_fTotalDistance = sqrt(powf((m_fTargetPosX - currentPosX), 2) + powf((m_fTargetPosY - currentPosY), 2));
	if (m_fTotalDistance <= Assets::get().GetSizeSprite()) {
		this->bCompleted = true;
	}
	else {
		// re-calculate seach component of velocity
		float m_fVx = ((m_fTargetPosX - currentPosX) / m_fTotalDistance);
		float m_fVy = ((m_fTargetPosY - currentPosY) / m_fTotalDistance);
		dynamic->addVelocityNormalizedXY(m_fVx, m_fVy);
	}
}


