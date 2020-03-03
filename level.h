#pragma once
#include "SFML/Graphics.hpp"
#include "maps.h"
#include "dynamic.h"
#include "creature.h"
#include "command.h"
#include "scriptProcessor.h"
#include "Interactive.h"
// Responsible for putting together all info of the game in that level
class Level {
public:
	Level();
	~Level();
	inline bool isAcceptingInputs() { return scriptProcessor.getUserControlEnabled();}
	void handleInputs(sf::Event event);
	void update();
	void draw(sf::RenderWindow* pWindow);

	//void switchMap(string targetMap);
	virtual void populateDynamics()=0;

protected:

	Timer timer;
	Creature* player;
	cScriptProcessor scriptProcessor;
	cTextDrawer textDrawer;
	vector<Dynamic*> vDynamic;
	vector<cCommand*> vCommands;

private:
	bool bPressedUp, bPressedRight, bPressedDown, bPressedLeft;
};


// <--- Level One --->

class cLevel_LevelOne : public Level {
public:
	cLevel_LevelOne();
	~cLevel_LevelOne();
	void populateDynamics() override;
};