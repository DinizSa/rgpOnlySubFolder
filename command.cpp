#include "command.h"
#include "assets.h"

cCommand::cCommand(){
	bCompleted = false;
	bStarted = false;
}

cCommand::~cCommand() {};

// <------------------------------- Talk Command ------------------------------->
cCommand_Talk::cCommand_Talk(string textToDisplay, int iMsDuration, sf::Color color) {
	iMsDisplaying = 0;
	this->iMsDuration = iMsDuration;
	this->textColor = color;
	this->textToDisplay = textToDisplay;
	bCompleted = false;
	bStarted = false;
};

cCommand_Talk::~cCommand_Talk() {
};

void cCommand_Talk::Start() {
	bCompleted = false;
	bStarted = true;
	cTextDrawer::get().setText( textToDisplay, textColor);
};

void cCommand_Talk::Update(int msElapsed) {
	iMsDisplaying += msElapsed;
	if (iMsDisplaying > iMsDuration) {
		this->bCompleted = true;
		cTextDrawer::get().removeText();
	}
};

// <------------------------------- Move Command ------------------------------->
cCommand_MoveTo::cCommand_MoveTo(Dynamic* dynamic, float x, float y) {
	this->dynamic = dynamic;
	this->m_fStartPosX = 0.f;
	this->m_fStartPosY = 0.f;
	m_fTargetPosX = x;
	m_fTargetPosY = y;
	bCompleted = false;
	bStarted = false;
}
cCommand_MoveTo::~cCommand_MoveTo() {

}

void cCommand_MoveTo::Start() {
	this->m_fStartPosX = dynamic->getPosX();
	this->m_fStartPosY = dynamic->getPosY();
	bStarted = true;
	bCompleted = false;

}

void cCommand_MoveTo::Update(int iElapsedTime) {
	float currentPosX = dynamic->getPosX();
	float currentPosY = dynamic->getPosY();
	float m_fTotalDistance = sqrt(powf((m_fTargetPosX - currentPosX), 2) + powf((m_fTargetPosY - currentPosY), 2));
	if (m_fTotalDistance <= Assets::get().GetSizeSprite("RespectableDistance")) {
		this->bCompleted = true;
	}
	else {
		// re-calculate seach component of velocity
		float m_fVx = ((m_fTargetPosX - currentPosX) / m_fTotalDistance);
		float m_fVy = ((m_fTargetPosY - currentPosY) / m_fTotalDistance);
		dynamic->addVelocityNormalizedXY(m_fVx, m_fVy);
	}
}


