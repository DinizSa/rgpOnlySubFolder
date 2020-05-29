#pragma once
#include "SFML/Graphics.hpp"
#include "maps.h"
#include "dynamic.h"
#include "creature.h"
#include "quest.h"
#include "constants.h"

// Responsible for putting together all life into the map
class cDynamicMap {
public:
	cDynamicMap();
	~cDynamicMap();
	void handleInputs(sf::Event event);
	void update();
	void draw(sf::RenderWindow* pWindow);
	inline int getPixelsW() {
		return cMap->getNrHorizontal() * constants::ASSET_SIZE;
	}
	inline int getPixelsH() {
		return cMap->getNrVertical() * constants::ASSET_SIZE;
	}
	inline string getName() { return sName; }
	virtual void populateDynamics(Dynamic* pPlayer)=0;
	void setFilter(sf::Color);

protected:
	string sName;
	Timer* pTimer;
	Maps* cMap;
	vector<Dynamic*> vDynamic;
	vector<Dynamic*> vDynamic_Projectile;
	bool bPressedUp, bPressedRight, bPressedDown, bPressedLeft;
	sf::RectangleShape rectFilter;

	void handleInteraction();
	void cleanProjectiles(vector<Dynamic*>&);
};


// <--- Level One  --->
class cDynamicMap_LevelOne : public cDynamicMap {
public:
	cDynamicMap_LevelOne();
	void populateDynamics(Dynamic* pPlayer) override;
};

// <--- Arena One  --->
class cDynamicMap_ArenaOne : public cDynamicMap {
public:
	cDynamicMap_ArenaOne();
	void populateDynamics(Dynamic* pPlayer) override;
};