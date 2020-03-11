#include "dynamicMap.h"
#include "assets.h"
#include "command.h"
#include "scriptProcessor.h"
#include "Interactive.h"

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
	cTextDrawer::get().drawText(pWindow);
}

void cDynamicMap::handleInputs(sf::Event event, vector<cQuest*> vQuest) {

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
			if (vDynamic[0]->getCollidingDynamic(&vDynamic) != nullptr) {
				Dynamic* collided = vDynamic[0]->getCollidingDynamic(&vDynamic);
				// With the following  implementation, quest interactions are more important than individual interactions
				for (auto quest : vQuest)
					if (quest->OnInteraction(vDynamic, collided))
						return; 
				collided->OnInteraction(vDynamic[0]);
			}
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

// <--------------------------- Populated Map: MapWildOne --------------------------->
cDynamicMap_One::cDynamicMap_One() {
	this->sName = "DynMap_WildOne";
	cMap = new Maps("MapWildOne");

};

cDynamicMap_One::~cDynamicMap_One() {};

void cDynamicMap_One::populateDynamics(Dynamic* pPlayer, vector<cQuest*> vQuest) {
	this->vDynamic.push_back(pPlayer);
	// Map characters
	this->vDynamic.push_back(new cCreature_FireLady(450, 500));
	this->vDynamic.push_back(new cCreature_EarthBender(550, 350));
	this->vDynamic.push_back(new cCreature_EvilRabbit(700, 500));
	this->vDynamic.push_back(new cCreature_PinkRabbit(700, 450));
	// Map Interactives
	this->vDynamic.push_back(new cInteractive_Teleport(700, 450, "DynMap_WildOneTrip", 460, 100));


	for (unsigned i = 0; i < vQuest.size(); i++)
		vQuest[i]->PopulateDynamics(vDynamic, this->sName);
}

// <--------------------------- Populated Map: MapWildTripOne --------------------------->
cDynamicMap_OneTrip::cDynamicMap_OneTrip() {
	this->sName = "DynMap_WildOneTrip";
	cMap = new Maps("MapWildOneTrip");

};

cDynamicMap_OneTrip::~cDynamicMap_OneTrip() {};

void cDynamicMap_OneTrip::populateDynamics(Dynamic* pPlayer, vector<cQuest*> vQuest) {
	this->vDynamic.push_back(pPlayer);
	// Map characters
	this->vDynamic.push_back(new cCreature_FireLady(350, 100));
	this->vDynamic.push_back(new cCreature_EarthBender(550, 650));
	// Map Interactives
	this->vDynamic.push_back(new cInteractive_Teleport(500, 100, "DynMap_WildOne", 660, 450));


	for (unsigned i = 0; i < vQuest.size(); i++)
		vQuest[i]->PopulateDynamics(this->vDynamic, this->sName);


	cScriptProcessor::Get().AddCommand(new cCommand_MoveTo(vDynamic[1], vDynamic[0]->getPosX(), vDynamic[0]->getPosY()));
	cScriptProcessor::Get().AddCommand(new cCommand_Talk("Damm dog", 1500, sf::Color::Black));
}