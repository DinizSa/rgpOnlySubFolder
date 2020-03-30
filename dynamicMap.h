#pragma once
#include "SFML/Graphics.hpp"
#include "maps.h"
#include "dynamic.h"
#include "creature.h"
#include "quest.h"

// Responsible for putting together all life into the map
class cDynamicMap {
public:
	cDynamicMap();
	~cDynamicMap();
	void handleInputs(sf::Event event);
	void update();
	void draw(sf::RenderWindow* pWindow);

	inline string getName() { return sName; }
	virtual void populateDynamics(Dynamic* pPlayer)=0;

protected:
	string sName;
	Timer* pTimer;
	Maps* cMap;
	vector<Dynamic*> vDynamic;
	vector<Dynamic*> vDynamic_Projectile;
	bool bPressedUp, bPressedRight, bPressedDown, bPressedLeft;

	void handleInteraction();
};


// <--- Level One --->
class cDynamicMap_One : public cDynamicMap {
public:
	cDynamicMap_One();
	~cDynamicMap_One();
	void populateDynamics(Dynamic* pPlayer) override;
};

// <--- Level One Trip --->
class cDynamicMap_OneTrip : public cDynamicMap {
public:
	cDynamicMap_OneTrip();
	~cDynamicMap_OneTrip();
	void populateDynamics(Dynamic* pPlayer) override;
};