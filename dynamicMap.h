#pragma once
#include "SFML/Graphics.hpp"
#include "maps.h"
#include "dynamic.h"
#include "creature.h"
#include "command.h"
#include "scriptProcessor.h"
#include "Interactive.h"
// Responsible for putting together all info of the game in that level
class cDynamicMap {
public:
	cDynamicMap();
	~cDynamicMap();
	inline bool isAcceptingInputs() { return scriptProcessor.getUserControlEnabled();}
	void handleInputs(sf::Event event);
	void update();
	void draw(sf::RenderWindow* pWindow);

	//void switchMap(string targetMap);
	virtual void populateDynamics()=0;
	inline string getName() { return sName; }
	inline void setpPlayer(Creature* pPlayer) { this->vDynamic[0]=pPlayer;/* this->vDynamic[0] = pPlayer;*/ }

protected:
	string sName;
	Timer* pTimer;
	//Creature* pPlayer;
	Maps* cMap;
	cScriptProcessor scriptProcessor;
	cTextDrawer textDrawer;
	vector<Dynamic*> vDynamic;
	vector<cCommand*> vCommands;
	bool bPressedUp, bPressedRight, bPressedDown, bPressedLeft;
};


// <--- Level One --->
class cDynamicMap_One : public cDynamicMap {
public:
	cDynamicMap_One();
	~cDynamicMap_One();
	void populateDynamics() override;
};

// <--- Level One Trip --->
class cDynamicMap_OneTrip : public cDynamicMap {
public:
	cDynamicMap_OneTrip();
	~cDynamicMap_OneTrip();
	void populateDynamics() override;
};