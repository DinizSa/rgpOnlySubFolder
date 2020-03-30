#include "item.h";
#include "creature.h";

cItem::cItem(string name, string asset, string desc, float px, float py, int iQuantity, bool consumable): Dynamic(name, asset, px, py, true, true, true, true, 1.f) {
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
cItem_ScrollBandidosTruth::cItem_ScrollBandidosTruth() :cItem("Bandido's scroll of truth", "scroll", "Bandido is a lil punk - Aristoteles", -1, -1, 1, false) {}

cItem_ScrollBandidosTruth::cItem_ScrollBandidosTruth(float px, float py) : cItem("Bandido's scroll of truth", "scroll", "Bandido is a lil punk - Aristoteles", px, py, 1, false) {
}

bool cItem_ScrollBandidosTruth::OnInteraction(Dynamic* dynamic) {
	return true; // Add to the inventory
}

void cItem_ScrollBandidosTruth::OnUse(Dynamic* dynamic) {
	// Maybe focus on scroll
}

// <------------------------------------------ Weapon ------------------------------------------>
cItem_Weapon::cItem_Weapon(string name, string asset, string description, int strength) :cItem(name, asset, description, -1, -1, 1, false) {
	this->iStrength = strength;
}

cItem_Weapon::cItem_Weapon(string name, string asset, string description, int strength, float px, float py) : cItem(name, asset, description, px, py, 1, false) {
	this->iStrength = strength;
}

bool cItem_Weapon::OnInteraction(Dynamic* dynamic) {
	return true; // Add to the inventory
}

// <------------------------------------------ Sword item ------------------------------------------>
cItem_Sword::cItem_Sword(int strength) :cItem_Weapon("Sword", "sword", "Steel sword, " + to_string(strength) + " attack", strength) {
}

cItem_Sword::cItem_Sword(int strength, float px, float py) : cItem_Weapon("Sword", "sword", "Steel sword, " + to_string(strength) + " attack", strength, px, py) {
}

bool cItem_Sword::OnInteraction(Dynamic* dynamic) {
	if (!dynamic->hasWeaponEquiped()) {
		dynamic->setWeapon(this);
	}
	return true; // Add to the inventory
}

cProjectile* cItem_Sword::OnWeaponUse(Dynamic* dynamic) {
	int direction = dynamic->geFacingDirection();

	float momentumX;
	float momentumY;
	switch (dynamic->geFacingDirection())
	{
	case 0: // South
		momentumX = 0.f;
		momentumY = 1.f;
		break;
	case 1: // West
		momentumX = -1.f;
		momentumY = 0.f;
		break;
	case 2: // North
		momentumX = 0.f;
		momentumY = -1.f;
		break;
	case 3: // East
		momentumX = 1.f;
		momentumY = 0.f;
		break;
	default:
		momentumX = 0.f;
		momentumY = 0.f;
		break;
	}
	//// Adds the momentum of the dynamic
	//float velX = momentumX + dynamic->getVelX()/dynamic->getMaxSpeed();
	//float velY = momentumY + dynamic->getVelY()/dynamic->getMaxSpeed();

	// Emits an projectile
	return new cProjectile_Fireball(dynamic->getPosX(), dynamic->getPosY(), momentumX, momentumY, true,this->iStrength);
}