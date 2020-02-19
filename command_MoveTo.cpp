#include "command_MoveTo.h"

cCommand_MoveTo::cCommand_MoveTo(Dynamic* dynamic, float x, float y) {
	this->dynamic = dynamic;
	m_fTargetPosX = x;
	m_fTargetPosY = y;	
	bCompleted = false;
}
cCommand_MoveTo::~cCommand_MoveTo() {

}

void cCommand_MoveTo::Start() {
	this->m_fStartPosX = dynamic->getPosX();
	this->m_fStartPosY = dynamic->getPosY();
	bStarted = true;


}

void cCommand_MoveTo::Update(int iElapsedTime) {
	float currentPosX = dynamic->getPosX();
	float currentPosY = dynamic->getPosY();
	float m_fTotalDistance = sqrt(powf((m_fTargetPosX - currentPosX), 2) + powf((m_fTargetPosY - currentPosY), 2));

	if (m_fTotalDistance <= dynamic->getMaxSpeed() * 2 ) {
		this->bCompleted = true;
	}
	else {
		// re-calculate seach component of velocity
		float m_fVx = ((m_fTargetPosX - currentPosX) / m_fTotalDistance);
		float m_fVy = ((m_fTargetPosY - currentPosY) / m_fTotalDistance);
		dynamic->addVelocityNormalizedXY(m_fVx, m_fVy);
	}
}