#include "item.h";
#include "creature.h";
#include "constants.h";
#include "scriptProcessor.h"

cItem::cItem(string name, string asset, string desc, float px, float py, int iQuantity, bool consumable): 
	Dynamic(name, asset, px, py, true, true, true, true, 1.f, false) {
	this->sName = name;
	this->sAsset = asset;
	this->sDesc = desc;
	this->iQuantity = iQuantity;
	this->iStrength = 0; // Not input becasue will not make sens to some
	this->consumable = consumable;
}

// Returns true if has some after update
bool cItem::updateQuantity(int quantity) { 
	this->iQuantity += quantity; 
	return this->iQuantity > 0;
}


void cItem::drawBorder(sf::RenderWindow* pWindow) {
	auto border = sf::RectangleShape(sf::Vector2f(this->getWidth(), this->getHeight()));
	border.setPosition(this->getPosX(), this->getPosY());
	border.setFillColor(sf::Color::Transparent);
	border.setOutlineColor(sf::Color::White);
	border.setOutlineThickness(5.f);
	pWindow->draw(border);
}


// <------------------------------------------ Health Potion Item ------------------------------------------>
cItem_HealthPotion::cItem_HealthPotion(int strength):cItem("Health Potion", "hearth", "Regenerates " + to_string(strength) + " points of health", -1, -1,1, true) {
	this->iStrength = strength;
}

cItem_HealthPotion::cItem_HealthPotion(int strength, float px, float py): cItem("Health Potion", "hearth", "Regenerates " + to_string(strength) + " points of health", px, py, 1, true) {
	this->iStrength = strength;
}

bool cItem_HealthPotion::OnInteraction(Dynamic* dynamic) {
	if ((((Creature*)dynamic)->getMaxHealth() - ((Creature*)dynamic)->getHealth()) < this->iStrength) // Less wounded than this would heal
		return true;
	else { // Add's to the inventory
		OnUse(dynamic);
		return false;
	}
}

void cItem_HealthPotion::OnUse(Dynamic* dynamic) {
	((Creature*)dynamic)->heal(this->iStrength);
}


// <------------------------------------------ Max Health Potion Item ------------------------------------------>
cItem_MaxHealthPotion::cItem_MaxHealthPotion(int strength):cItem("Max Health Potion", "shroom", "Increases maximum health by " + to_string(strength) + " points", -1, -1,1, true) {
	this->iStrength = strength;
}

cItem_MaxHealthPotion::cItem_MaxHealthPotion(int strength, float px, float py): cItem("Max Health Potion", "shroom", "Increases maximum health by " + to_string(strength) + " points", px, py, 1, true) {
	this->iStrength = strength;
}

bool cItem_MaxHealthPotion::OnInteraction(Dynamic* dynamic) {
	return true; // Add to the inventory
}

void cItem_MaxHealthPotion::OnUse(Dynamic* dynamic) {
	((Creature*)dynamic)->increaseMaxHealth(this->iStrength);
	((Creature*)dynamic)->heal(this->iStrength);
}

// <------------------------------------------ Scroll Item ------------------------------------------>
cItem_Scroll::cItem_Scroll() :cItem("Starting Scroll", "scroll", "", -1, -1, 1, false) {}

cItem_Scroll::cItem_Scroll(float px, float py) : cItem("Starting Scroll", "scroll", "", px, py, 1, false) {
}

bool cItem_Scroll::OnInteraction(Dynamic* dynamic) {

	return true; // Add to the inventory
}

void cItem_Scroll::OnUse(Dynamic* dynamic) {
	// Maybe focus on scroll
}

// <------------------------------------------ Calcetine Item ------------------------------------------>
cItem_Calcetine::cItem_Calcetine() :cItem("Meia", "sock", "Meia que chiera a erva", -1, -1, 1, false) {}

cItem_Calcetine::cItem_Calcetine(float px, float py) : cItem("Meia", "scroll", "Meia que cheira a erva", px, py, 1, false) {
}

bool cItem_Calcetine::OnInteraction(Dynamic* dynamic) {
	return true; // Add to the inventory
}

void cItem_Calcetine::OnUse(Dynamic* dynamic) {
	// Maybe focus on scroll
}


// <------------------------------------------ Weapon ------------------------------------------>
cItem_Weapon::cItem_Weapon(string name, string asset, string description, int strength, int rechargeTime, float px, float py) : cItem(name, asset, description, px, py, 1, false) {
	this->iStrength = strength;
	momentumX = 0.f;
	momentumY = 0.f;
	this->rechargeTime = rechargeTime;
	timeSinceLastShoot = 0;
	this->timer = Timer();
}

bool cItem_Weapon::OnInteraction(Dynamic* dynamic) {
	return true; // Add to the inventory
}

// <------------------------------------------ Earth Ring Item ------------------------------------------>
cItem_EarthRing::cItem_EarthRing(int strength, float px, float py) : cItem_Weapon("Earth Ring", "Rings", "Earth bending ring, " + to_string(strength) + " power", strength, 2000, px, py) {
	this->setPartialTexture(constants::ASSET_SIZE * 1, 0, constants::ASSET_SIZE, constants::ASSET_SIZE);
}

bool cItem_EarthRing::OnInteraction(Dynamic* dynamic) {
	if (!dynamic->hasWeaponEquiped()) {
		dynamic->setWeapon(this);
	}
	return true; // Add to the inventory
}

cProjectile* cItem_EarthRing::OnWeaponUse(Dynamic* dynamic) {
	// TODO: passar isto pa função do pai
	this->timer.updateTimer();
	int timeSinceShoot = this->timer.getMsSinceStart();
	// Emits an projectile
	if (timeSinceShoot > rechargeTime) {
		this->timer.resetTime();
		return new cProjectile_Fireball(dynamic->getPosX() / constants::ASSET_SIZE, dynamic->getPosY() / constants::ASSET_SIZE, dynamic->getMomentumX(), dynamic->getMomentumY(), dynamic->isFriendly(), this->iStrength);
	}
	else
		return nullptr;
}

// <------------------------------------------ Sword Item ------------------------------------------>
cItem_Sword::cItem_Sword(int strength, float px, float py) : cItem_Weapon("Sword", "Sword", "Basic sword, " + to_string(strength) + " power", strength, 1000, px, py) {
}

bool cItem_Sword::OnInteraction(Dynamic* dynamic) {
	if (!dynamic->hasWeaponEquiped()) {
		dynamic->setWeapon(this);
	}
	return true; // Add to the inventory
}

cProjectile* cItem_Sword::OnWeaponUse(Dynamic* dynamic) {
	// TODO: passar isto pa função do pai
	this->timer.updateTimer();
	int timeSinceShoot = this->timer.getMsSinceStart();
	// Emits an projectile
	if (timeSinceShoot > rechargeTime) {
		this->timer.resetTime();
		return new cProjectile_Sword(dynamic->getPosX() / constants::ASSET_SIZE, dynamic->getPosY() / constants::ASSET_SIZE, dynamic->getMomentumX()/100, dynamic->getMomentumY()/100, dynamic->isFriendly(), this->iStrength);
	}
	else
		return nullptr;
}