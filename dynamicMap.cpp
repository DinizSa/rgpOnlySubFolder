#include "dynamicMap.h"
#include "assets.h"
#include "command.h"
#include "scriptProcessor.h"
#include "Interactive.h"
#include "item.h"
#include <algorithm>
#include "constants.h"

cDynamicMap::cDynamicMap() {
	this->bPressedLeft = false;
	this->bPressedRight = false;
	this->bPressedUp = false;
	this->bPressedDown = false;
	pTimer = new Timer;
	pTimer->updateTimer();

	vDynamic_Projectile.reserve(20);
	vDynamic_Projectile.reserve(50);
}

cDynamicMap::~cDynamicMap() {
	delete pTimer;
	delete cMap;
	for (auto& source : { &vDynamic, &vDynamic_Projectile }) {
		for (auto dynamic : *source)
			if (dynamic!=vDynamic[0])
				delete dynamic;
	}
	vDynamic.clear();
	vDynamic_Projectile.clear();
}

void cDynamicMap::update() {
	pTimer->updateTimer();
	cScriptProcessor::Get().ProcessCommands(pTimer->getMsSinceLastFrame());

	if (cScriptProcessor::Get().getUserControlEnabled()) { // Freezes during commands

		for (auto& source : { &vDynamic, &vDynamic_Projectile }) {
			for (auto dynamic : *source) {
				dynamic->update(pTimer, cMap, &vDynamic);

				// Check for projectile hits
				if (dynamic->isProjectile()) {
					auto collided = dynamic->getColliding(vDynamic);
					if (collided) {
						dynamic->OnInteraction(collided);
					}
				}
				// Check for triggers gatilhados
				if (dynamic->isAttacking()) {
					auto projetile = dynamic->attackWeapon();
					if (projetile) { // Defined if weapon pew pew
						this->vDynamic_Projectile.push_back(projetile);
					}
					if (!dynamic->isFriendly()) // If is an enemy shooting, call interaction (might be usefull, to trigger a battle for example)
						dynamic->OnInteraction(vDynamic[0]);
					dynamic->setAttacking(false);
				}
			}
		}

		// Remove projectiles that lost their energy
		auto it = vDynamic_Projectile.begin();
		for (unsigned i = 0; i < vDynamic_Projectile.size(); i++)
		{
			if (!((cProjectile*)(vDynamic_Projectile[i]))->isEnergized()) {
				delete vDynamic_Projectile[i];
				vDynamic_Projectile.erase(it);
			}
			else {
				++it;
			}
		}

		// Player movement
		if (bPressedLeft)
			vDynamic[0]->addVelocityNormalizedX(-1.f);
		if (bPressedRight)
			vDynamic[0]->addVelocityNormalizedX(1.f);
		if (bPressedUp)
			vDynamic[0]->addVelocityNormalizedY(-1.f);
		if (bPressedDown)
			vDynamic[0]->addVelocityNormalizedY(1.f);

	}
}


void cDynamicMap::draw(sf::RenderWindow* pWindow) {
	cMap->draw(pWindow, vDynamic[0]->getVelX(), vDynamic[0]->getVelY());
	for (auto& source : { &vDynamic, &vDynamic_Projectile }) {
		for (auto dynamic : *source)
			dynamic->draw(pWindow);
	}

	
	vDynamic[0]->draw(pWindow);
	cTextDrawer::get().drawText_MapMode(pWindow);
}

void cDynamicMap::handleInputs(sf::Event event) {

	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::A)
			this->bPressedLeft = true;
		if (event.key.code == sf::Keyboard::D)
			this->bPressedRight = true;
		if (event.key.code == sf::Keyboard::W)
			this->bPressedUp = true;
		if (event.key.code == sf::Keyboard::S)
			this->bPressedDown = true;
		if (event.key.code == sf::Keyboard::Space)
			handleInteraction();
		if (event.key.code == sf::Keyboard::E && vDynamic[0]->hasWeaponEquiped()) {
			vDynamic[0]->setAttacking(true);
		}
	}

	// Keys released
	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::A)
			this->bPressedLeft = false;
		if (event.key.code == sf::Keyboard::D)
			this->bPressedRight = false;
		if (event.key.code == sf::Keyboard::W)
			this->bPressedUp = false;
		if (event.key.code == sf::Keyboard::S)
			this->bPressedDown = false;
	}
}

void cDynamicMap::handleInteraction() {
	Dynamic* collided = vDynamic[0]->getCollidingFront(&vDynamic);
	if (collided != nullptr) {
		// Quests
		for (unsigned i = 0; i < cQuest::getQuestVector()->size(); i++)
			if ((*cQuest::getQuestVector())[i]->OnInteraction(vDynamic, collided))
				return;
		// Items
		if (dynamic_cast<cItem*>(collided)) {
			if (collided->OnInteraction(vDynamic[0])) {
				// If an item returns true, is to add
				vDynamic[0]->addItem(collided);
			}
			// Remove from the map, and add to the dynamic player
			vDynamic.erase(remove(vDynamic.begin(), vDynamic.end(), collided), vDynamic.end());
			return;
		}
		// All others dynamics
		collided->OnInteraction(vDynamic[0]);
		return;
	}
}

// <--------------------------- Populated Map: MapWildOne --------------------------->
cDynamicMap_One::cDynamicMap_One() {
	this->sName = "DynMap_WildOne";
	cMap = new Maps("MapWildOne");

};

cDynamicMap_One::~cDynamicMap_One() {};

void cDynamicMap_One::populateDynamics(Dynamic* pPlayer) {
	this->vDynamic.push_back(pPlayer);
	// Map characters
	this->vDynamic.push_back(new cCreature_FireLady("Matilda", 11, 12));
	this->vDynamic.push_back(new cCreature_EarthBender("Gustavo Santos", 12, 7));
	this->vDynamic.push_back(new cCreature_EvilRabbit("Evil Rabbit", 16, 13));
	this->vDynamic.push_back(new cCreature_PinkRabbit("Pink Rabbit", 16, 7));
	// Map Interactives
	this->vDynamic.push_back(new cInteractive_Teleport(18, 12, "DynMap_WildOneTrip", 11, 10 ));
	// Items
	this->vDynamic.push_back(new cItem_HealthPotion(10, 2, 16));
	this->vDynamic.push_back(new cItem_EarthRing(10, 14, 16));

	for (unsigned i = 0; i < cQuest::getQuestVector()->size(); i++)
		(*cQuest::getQuestVector())[i]->PopulateDynamics(vDynamic, this->sName);

}

// <--------------------------- Populated Map: MapWildTripOne --------------------------->
cDynamicMap_OneTrip::cDynamicMap_OneTrip() {
	this->sName = "DynMap_WildOneTrip";
	cMap = new Maps("MapWildOneTrip");

};

cDynamicMap_OneTrip::~cDynamicMap_OneTrip() {};

void cDynamicMap_OneTrip::populateDynamics(Dynamic* pPlayer) {
	this->vDynamic.push_back(pPlayer);
	// Map characters
	this->vDynamic.push_back(new cCreature_FireLady("Matilda sister", 10, 6));
	this->vDynamic.push_back(new cCreature_EarthBender("Joseph brother", 5, 12));
	// Map Interactives
	this->vDynamic.push_back(new cInteractive_Teleport(12, 10, "DynMap_WildOne", 17 , 12 ));
	// Items
	this->vDynamic.push_back(new cItem_MaxHealthPotion(5, 3, 3));

	for (unsigned i = 0; i < cQuest::getQuestVector()->size(); i++)
		(*cQuest::getQuestVector())[i]->PopulateDynamics(vDynamic, this->sName);

}

// <--------------------------- Populated Map: Level One --------------------------->
cDynamicMap_LevelOne::cDynamicMap_LevelOne() {
	this->sName = "DynMap_LevelOne";
	cMap = new Maps("MapLevelOne"); 
	
}

void cDynamicMap_LevelOne::populateDynamics(Dynamic* pPlayer) {
	// Life
	this->vDynamic.push_back(pPlayer);
	this->vDynamic.push_back(new cCreature_EarthBender("Earth Bender", 10, 4));
	this->vDynamic.push_back(new cCreature_PinkRabbit("Rabbit", 15, 6));
	this->vDynamic.push_back(new cCreature_PinkRabbit("Rabbit", 12, 4));
	// Interactives
	this->vDynamic.push_back(new cInteractive_Info("Stone friend", 2, 4));
	this->vDynamic.push_back(new cInteractive_Teleport(16, 6, "DynMap_ArenaOne", 5, 5));

	this->cMap->setBackground(vDynamic[0]->getPosX(), vDynamic[0]->getPosY());

	for (unsigned i = 0; i < cQuest::getQuestVector()->size(); i++) {
		(*cQuest::getQuestVector())[i]->PopulateDynamics(vDynamic, this->sName);
	}

}

// <--------------------------- Populated Map: Arena One --------------------------->
cDynamicMap_ArenaOne::cDynamicMap_ArenaOne() {
	this->sName = "DynMap_ArenaOne";
	cMap = new Maps("MapLevelOne");

}

void cDynamicMap_ArenaOne::populateDynamics(Dynamic* pPlayer) {
	// Life
	this->vDynamic.push_back(pPlayer);
	this->vDynamic.push_back(new cCreature_EvilRabbit("Rabbit", 15, 6));
	this->vDynamic.push_back(new cCreature_EvilRabbit("Rabbit", 16, 4));
	this->vDynamic.push_back(new cCreature_EvilRabbit("Rabbit", 9, 6));
	this->vDynamic.push_back(new cCreature_EvilRabbit("Rabbit", 7, 3));
	// Interactives
	this->vDynamic.push_back(new cInteractive_Teleport(5, 6, "DynMap_LevelOne", 16, 5));

	for (unsigned i = 0; i < cQuest::getQuestVector()->size(); i++) {
		(*cQuest::getQuestVector())[i]->PopulateDynamics(vDynamic, this->sName);
	}

}