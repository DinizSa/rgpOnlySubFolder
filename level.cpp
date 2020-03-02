#include "level.h"
#include "assets.h"

Level::Level() {
	pCurrentMap = nullptr;
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
		dynamic->update(&timer, pCurrentMap, &vDynamic);
	}
}

void Level::switchMap(string targetMap) {
	pCurrentMap = Assets::get().GetMaps(targetMap);
}

void Level::draw(sf::RenderWindow* pWindow) {
	pCurrentMap->draw(pWindow);
	for (auto dynamic : vDynamic) {
		dynamic->draw(pWindow);
	}
	textDrawer.drawText(pWindow);
}

void Level::handleInputs(sf::RenderWindow* pWindow, InputHandler inputHandler) {
	scriptProcessor.ProcessCommands(timer.getMsSinceLastFrame());
	// Handle inputs if not running a command
	if (scriptProcessor.getUserControlEnabled())
		inputHandler.pollEvents(pWindow, &vDynamic, player);
}


// <--------------------------- Level One --------------------------->
cLevel_LevelOne::cLevel_LevelOne() {
	populateDynamics();
	pCurrentMap = Assets::get().GetMaps("MapWildOne");


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
	vDynamic.push_back(new Interactive("RedFlowers", 700, 450, 34, 34));

}