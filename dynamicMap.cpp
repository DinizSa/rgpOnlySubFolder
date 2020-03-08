#include "dynamicMap.h"
#include "assets.h"

cDynamicMap::cDynamicMap() {
	this->bPressedLeft = false;
	this->bPressedRight = false;
	this->bPressedUp = false;
	this->bPressedDown = false;
	pTimer = new Timer;
	pTimer->updateTimer();
	vDynamic.clear();
	// Save space for the player
	vDynamic.push_back(new Creature("PackMan", 400, 450, 1, 1, 1, 100, 2.0f));
}

cDynamicMap::~cDynamicMap() {
	delete pTimer;
	for (unsigned i = 0; i < vCommands.size(); i++)
		delete vCommands[i];
	delete cMap;
	for (unsigned i = 1; i < vDynamic.size(); i++)
		delete vDynamic[i];
}

void cDynamicMap::update() {
	pTimer->updateTimer();
	scriptProcessor.ProcessCommands(pTimer->getMsSinceLastFrame());

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
	textDrawer.drawText(pWindow);
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

	// Commands TODO: put in the right place
	vCommands.push_back(new cCommand_MoveTo(vDynamic[2], vDynamic[0]->getPosX(), vDynamic[0]->getPosY()));
	vCommands.push_back(new cCommand_Talk(&textDrawer, "Man you can eat those flowers! ", 1500, sf::Color::Black));
	for (auto command : vCommands)
		scriptProcessor.AddCommand(command);
};

cDynamicMap_One::~cDynamicMap_One() {};

void cDynamicMap_One::populateDynamics() {
	// pPlayer
	//vDynamic.push_back(pPlayer);
	// Secondary characters
	vDynamic.push_back(new Creature("FireLady", 550, 500, 1, 1, 1, 50, 1.5f));
	vDynamic.push_back(new Creature("EarthBender", 650, 500,1, 1, 1, 50, 1.5f));
	// Map Interactives
	vDynamic.push_back(new cInteractive_Teleport(700, 450, "DynMap_WildOneTrip", 460, 100));

}

// <--------------------------- Populated Map: MapWildTripOne --------------------------->
cDynamicMap_OneTrip::cDynamicMap_OneTrip() {
	cout << "init" << endl;
	this->sName = "DynMap_WildOneTrip";
	cMap = new Maps("MapWildOneTrip");
	populateDynamics();

	// Commands TODO: put in the right place
	vCommands.push_back(new cCommand_MoveTo(vDynamic[1], vDynamic[0]->getPosX(), vDynamic[0]->getPosY()));
	vCommands.push_back(new cCommand_Talk(&textDrawer, "I am so high right now... ", 1500, sf::Color::Black));
	vCommands.push_back(new cCommand_Talk(&textDrawer, "I dont even know what's going on", 1500, sf::Color::Black));
	for (auto command : vCommands)
		scriptProcessor.AddCommand(command);
};

cDynamicMap_OneTrip::~cDynamicMap_OneTrip() {};

void cDynamicMap_OneTrip::populateDynamics() {
	// Secondary characters
	vDynamic.push_back(new Creature("FireLady", 550, 500, 1, 1, 1, 50, 1.5f));
	vDynamic.push_back(new Creature("EarthBender", 650, 500, 1, 1, 1, 50, 1.5f));
	// Map Interactives
	vDynamic.push_back(new cInteractive_Teleport(500, 100, "DynMap_WildOne", 660, 450));

}