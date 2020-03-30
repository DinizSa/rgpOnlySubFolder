#include "dynamicMap.h"
#include "assets.h"
#include "command.h"
#include "scriptProcessor.h"
#include "Interactive.h"
#include "item.h"
#include <algorithm>

cDynamicMap::cDynamicMap() {
	this->bPressedLeft = false;
	this->bPressedRight = false;
	this->bPressedUp = false;
	this->bPressedDown = false;
	pTimer = new Timer;
	pTimer->updateTimer();


}

cDynamicMap::~cDynamicMap() {
	delete pTimer;
	delete cMap;
	for (unsigned i = 1; i < vDynamic.size(); i++)
		delete vDynamic[i];
	vDynamic.clear();
}

void cDynamicMap::update() {
	pTimer->updateTimer();
	cScriptProcessor::Get().ProcessCommands(pTimer->getMsSinceLastFrame());

	for (auto dynamic: vDynamic)
		dynamic->update(pTimer, cMap, &vDynamic);

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


void cDynamicMap::draw(sf::RenderWindow* pWindow) {
	cMap->draw(pWindow);
	for (unsigned i = 1; i < vDynamic.size(); i++) 
		vDynamic[i]->draw(pWindow);
	
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
	}

	// Movement released
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
	if (vDynamic[0]->getCollidingDynamic(&vDynamic) != nullptr) {
		Dynamic* collided = vDynamic[0]->getCollidingDynamic(&vDynamic);
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
			// REmove from the map, and add to the dynamic player
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
	this->vDynamic.push_back(new cCreature_FireLady("Matilda", 450, 500));
	this->vDynamic.push_back(new cCreature_EarthBender("Joseph", 550, 350));
	this->vDynamic.push_back(new cCreature_EvilRabbit("Evil Rabbit", 700, 500));
	this->vDynamic.push_back(new cCreature_PinkRabbit("Pink Rabbit", 700, 350));
	// Map Interactives
	this->vDynamic.push_back(new cInteractive_Teleport(700, 450, "DynMap_WildOneTrip", 460, 100));
	// Items
	this->vDynamic.push_back(new cItem_HealthPotion(10, 50.f, 400.f));
	this->vDynamic.push_back(new cItem_Sword(10, 550.f, 400.f));

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
	this->vDynamic.push_back(new cCreature_FireLady("Matilda sister", 350, 100));
	this->vDynamic.push_back(new cCreature_EarthBender("Joseph brother", 150, 50));
	// Map Interactives
	this->vDynamic.push_back(new cInteractive_Teleport(500, 100, "DynMap_WildOne", 660, 450));
	// Items
	this->vDynamic.push_back(new cItem_MaxHealthPotion(5, 90.f, 400.f));

	for (unsigned i = 0; i < cQuest::getQuestVector()->size(); i++)
		(*cQuest::getQuestVector())[i]->PopulateDynamics(vDynamic, this->sName);

	cScriptProcessor::Get().AddCommand(new cCommand_MoveTo(vDynamic[1], vDynamic[0]->getPosX(), vDynamic[0]->getPosY()));
	cScriptProcessor::Get().AddCommand(new cCommand_Talk("Hi this world is the same as \nthe previous... ", 1500, sf::Color::Black));
	cScriptProcessor::Get().AddCommand(new cCommand_Talk("... but on drugs! ", 1500, sf::Color::Black));
	cScriptProcessor::Get().AddCommand(new cCommand_Talk("You must get out of this trip man! ", 1500, sf::Color::Black));
}