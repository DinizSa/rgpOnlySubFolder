#include "level.h"
#include "assets.h"

Level::Level() {
	this->bPressedLeft = false;
	this->bPressedRight = false;
	this->bPressedUp = false;
	this->bPressedDown = false;

	timer.updateTimer();
	vDynamic.clear();
	player = new Creature("PackMan", 400, 450, 0, 0, 34, 34, 1, 1, 1, 100, 1);
}

Level::~Level() {
	delete player;
	for (int i = 0; i < vDynamic.size(); i++)
		delete vDynamic[i];

}

void Level::update() {
	timer.updateTimer();
	scriptProcessor.ProcessCommands(timer.getMsSinceLastFrame());

	for (auto dynamic: vDynamic){
		dynamic->update(&timer, Assets::get().GetMaps(Assets::get().GetPresentMap()), &vDynamic);
	}
}


void Level::draw(sf::RenderWindow* pWindow) {
	Assets::get().GetMaps(Assets::get().GetPresentMap())->draw(pWindow);
	for (int i = 1; i < vDynamic.size(); i++) {
		vDynamic[i]->draw(pWindow);
	}
	player->draw(pWindow);
	textDrawer.drawText(pWindow);
}

void Level::handleInputs(sf::Event event) {

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
			if (player->getCollidingDynamic(&vDynamic) != nullptr) 
				player->getCollidingDynamic(&vDynamic)->OnInteraction(player);
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

	if (bPressedLeft)
		player->addVelocityNormalizedX(-1.f);
	if (bPressedRight)
		player->addVelocityNormalizedX(1.f);
	if (bPressedUp)
		player->addVelocityNormalizedY(-1.f);
	if (bPressedDown)
		player->addVelocityNormalizedY(1.f);

}


// <--------------------------- Level One --------------------------->
cLevel_LevelOne::cLevel_LevelOne() {
	populateDynamics();
	Assets::get().SetPresentMap("MapWildOne");


	// Commands TODO: put in the right place
	
	vCommands.push_back(new cCommand_MoveTo(vDynamic[2], player->getPosX(), player->getPosY()));
	vCommands.push_back(new cCommand_Talk(&textDrawer, "hi", "Hey! ", 1000, sf::Color::Red));
	vCommands.push_back(new cCommand_Talk(&textDrawer, "hiBack", "Hi! ", 1000, sf::Color::Blue));
	for (auto command : vCommands)
		scriptProcessor.AddCommand(command);
};

cLevel_LevelOne::~cLevel_LevelOne() {
	//for (auto dynamic : vDynamic)
	//	delete dynamic;
	vDynamic.clear();
	for (int i = 0; i < vCommands.size(); i++)
		delete vCommands[i];

};


void cLevel_LevelOne::populateDynamics() {
	// Player
	vDynamic.push_back(player);
	// Secondary characters
	vDynamic.push_back(new Creature("FireLady", 550, 500, 0, 0, 34, 34, 1, 1, 1, 50, 1));
	vDynamic.push_back(new Creature("EarthBender", 650, 500, 0, 0, 34, 34, 1, 1, 1, 50, 1));
	// Map Interactives
	vDynamic.push_back(new cInteractive_Teleport(700, 450, "MapWildOneTrip", 500, 100));

}