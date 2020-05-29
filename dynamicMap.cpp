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

	setFilter(sf::Color(0, 0, 0, 0));
	
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

void cDynamicMap::setFilter(sf::Color color) {
	rectFilter = sf::RectangleShape(sf::Vector2f(constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT));
	rectFilter.setFillColor(color);
	rectFilter.setPosition(0, 0);
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

		cleanProjectiles(vDynamic_Projectile);



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


// Remove projectiles that lost their energy. Erase one each time to prevent crash.
void cDynamicMap::cleanProjectiles(vector<Dynamic*>& vector) {

	int indice = 0;
	auto it = vector.begin();
	for (unsigned i = 0; i < vector.size(); i++) {
		if (!((cProjectile*)(vector[i]))->isEnergized()) {
			cout << "AAAA size projectiles:" << vector.size() << ", indice: " << i << endl;
			vector.erase(it);
			cout << "AAAA" << endl;
			return;
		}
		else {
			indice++;
			cout << "BBBB size projectiles:" << vector.size() << ", incrementing to: " << indice << endl;
			it++;
			cout << "BBBB" << endl;
		}
	}
}


void cDynamicMap::draw(sf::RenderWindow* pWindow) {
	cMap->draw(pWindow, vDynamic[0]->getVelX(), vDynamic[0]->getVelY());
	for (auto& source : { &vDynamic, &vDynamic_Projectile }) {
		for (auto dynamic : *source)
			dynamic->draw(pWindow);
	}

	
	vDynamic[0]->draw(pWindow);
	
	pWindow->draw(this->rectFilter);

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



// <--------------------------- Populated Map: Level One --------------------------->
cDynamicMap_LevelOne::cDynamicMap_LevelOne() {
	this->sName = "DynMap_LevelOne";
	cMap = new Maps("MapLevelOne"); 
}

void cDynamicMap_LevelOne::populateDynamics(Dynamic* pPlayer) {
	// Life
	this->vDynamic.push_back(pPlayer);
	this->vDynamic.push_back(new cCreature_EarthBender("Earth Bender", 10, 4));
	this->vDynamic.push_back(new cCreature_PinkRabbit("Rabbit", 13, 6));
	this->vDynamic.push_back(new cCreature_PinkRabbit("Rabbit", 12, 4));
	// Interactives
	this->vDynamic.push_back(new cInteractive_Info("Stone friend", 2, 4));
	this->vDynamic.push_back(new cInteractive_Teleport(16, 6, "DynMap_ArenaOne", 5, 5));
	this->cMap->setBackground("bgpCloudsIsland", 1024, 1024, vDynamic[0]->getPosX(), vDynamic[0]->getPosY());

	for (unsigned i = 0; i < cQuest::getQuestVector()->size(); i++) {
		(*cQuest::getQuestVector())[i]->PopulateDynamics(vDynamic, this->sName);
	}

}

// <--------------------------- Populated Map: Arena One --------------------------->
cDynamicMap_ArenaOne::cDynamicMap_ArenaOne() {
	this->sName = "DynMap_ArenaOne";
	cMap = new Maps("MapArenaOne");
	//this->setFilter(sf::Color(200, 100, 100, 80));
	this->setFilter(sf::Color(0, 0, 0, 0));
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

	this->cMap->setBackground("bgpSunset", 1920, 1080, vDynamic[0]->getPosX(), vDynamic[0]->getPosY());

	for (unsigned i = 0; i < cQuest::getQuestVector()->size(); i++) {
		(*cQuest::getQuestVector())[i]->PopulateDynamics(vDynamic, this->sName);
	}

}