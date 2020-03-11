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
	vDynamic.clear();
	vDynamic.push_back(new Creature("PackMan", 400, 450, 1, 1, 1, 100, 2.0f));



	vQuest.push_back(new cQuest_Base());
}

cDynamicMap::~cDynamicMap() {
	delete pTimer;
	delete cMap;
	for (unsigned i = 1; i < vDynamic.size(); i++)
		delete vDynamic[i];
	for (unsigned i = 0; i < vQuest.size(); i++)
		delete vQuest[i];
}

void cDynamicMap::update() {
	pTimer->updateTimer();
	cScriptProcessor::Get().ProcessCommands(pTimer->getMsSinceLastFrame());

	for (auto dynamic: vDynamic){
		dynamic->update(pTimer, cMap, &vDynamic);
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


void cDynamicMap::draw(sf::RenderWindow* pWindow) {
	cMap->draw(pWindow);
	for (unsigned i = 1; i < vDynamic.size(); i++) {
		vDynamic[i]->draw(pWindow);
	}
	vDynamic[0]->draw(pWindow);
	cTextDrawer::get().drawText(pWindow);
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
			if (vDynamic[0]->getCollidingDynamic(&vDynamic) != nullptr)
				vDynamic[0]->getCollidingDynamic(&vDynamic)->OnInteraction(vDynamic[0]);
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
	populateDynamics();

};

cDynamicMap_One::~cDynamicMap_One() {};

void cDynamicMap_One::populateDynamics() {
	// Map characters
	vDynamic.push_back(new cCreature_FireLady(450, 500));
	vDynamic.push_back(new cCreature_EarthBender(550, 350));
	vDynamic.push_back(new cCreature_EvilRabbit(700, 500));
	vDynamic.push_back(new cCreature_PinkRabbit(700, 450));
	// Map Interactives
	vDynamic.push_back(new cInteractive_Teleport(700, 450, "DynMap_WildOneTrip", 460, 100));


	for (unsigned i = 0; i < vQuest.size(); i++)
		vQuest[i]->PopulateDynamics(vDynamic, this->sName);
}

// <--------------------------- Populated Map: MapWildTripOne --------------------------->
cDynamicMap_OneTrip::cDynamicMap_OneTrip() {
	this->sName = "DynMap_WildOneTrip";
	cMap = new Maps("MapWildOneTrip");
	populateDynamics();

	cScriptProcessor::Get().AddCommand(new cCommand_MoveTo(vDynamic[1], vDynamic[0]->getPosX(), vDynamic[0]->getPosY()));
	cScriptProcessor::Get().AddCommand(new cCommand_Talk("Damm dog", 1500, sf::Color::Black));


};

cDynamicMap_OneTrip::~cDynamicMap_OneTrip() {};

void cDynamicMap_OneTrip::populateDynamics() {
	// Map characters
	vDynamic.push_back(new cCreature_FireLady(450, 500));
	vDynamic.push_back(new cCreature_EarthBender(550, 650));
	// Map Interactives
	vDynamic.push_back(new cInteractive_Teleport(500, 100, "DynMap_WildOne", 660, 450));


	for (unsigned i = 0; i < vQuest.size(); i++)
		vQuest[i]->PopulateDynamics(vDynamic, this->sName);


}