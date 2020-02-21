#pragma once
#include "commands.h"
#include "textDrawer.h"
//#include "SFML/Graphics.hpp"

class cCommand_Talk : public cCommand {
public:
	cCommand_Talk(cTextDrawer* pTextDrawer, string textName, string textToDisplay, int iMsDuration, sf::Color color = sf::Color::Blue);
	~cCommand_Talk();

	inline void finish() { this->bCompleted = true; };
	void Start() override;
	void Update(int msElapsed) override;

private:
	int iMsDisplaying;
	int iMsDuration;
	sf::Color textColor;
	string textName;
	string textToDisplay;
	cTextDrawer* pTextDrawer;
};