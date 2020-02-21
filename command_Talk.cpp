#include "command_Talk.h"

cCommand_Talk::cCommand_Talk(cTextDrawer* pTextDrawer, string textName, string textToDisplay, int iMsDuration, sf::Color color) {
	iMsDisplaying = 0;
	this->iMsDuration = iMsDuration;
	this->textColor = color;
	this->textName = textName;
	this->textToDisplay = textToDisplay;
	this->pTextDrawer = pTextDrawer;
};

cCommand_Talk::~cCommand_Talk() {
};

void cCommand_Talk::Start() {
	pTextDrawer->setText(textName, textToDisplay, textColor);
};

void cCommand_Talk::Update(int msElapsed) {
	iMsDisplaying += msElapsed;
	if (iMsDisplaying > iMsDuration) {
		this->bCompleted = true;
		pTextDrawer->removeText(textName);
	}
};