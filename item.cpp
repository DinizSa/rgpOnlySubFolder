#include "item.h";
#include "creature.h";

cItem::cItem(string name, string asset, string desc, float px, float py, int iQuantity): Dynamic(name, asset, px, py, true, true, true, true, 1.f) {
	this->sName = name;
	this->sAsset = asset;
	this->sDesc = desc;
	this->iQuantity = iQuantity;
}


// <------------------------------------------ Health Potion Item ------------------------------------------>
cItem_HealthPotion::cItem_HealthPotion(int strength):cItem("Health Potion", "hearth", "Drink to regenerate health", -1, -1,1) {
	this->iStrength = strength;
}

cItem_HealthPotion::cItem_HealthPotion(int strength, float px, float py): cItem("Health Potion", "hearth", "Drink to regenerate health", px, py, 1) {
	this->iStrength = strength;
}

bool cItem_HealthPotion::OnInteraction(Dynamic* dynamic) {
	OnUse(dynamic);
	return false;
}

void cItem_HealthPotion::OnUse(Dynamic* dynamic) {
	((Creature*)dynamic)->heal(this->iStrength);
}


// <------------------------------------------ Max Health Potion Item ------------------------------------------>
cItem_MaxHealthPotion::cItem_MaxHealthPotion(int strength):cItem("Max Health Potion", "shroom", "Drink to increase maximum health", -1, -1,1) {
	this->iStrength = strength;
}

cItem_MaxHealthPotion::cItem_MaxHealthPotion(int strength, float px, float py): cItem("Max Health Potion", "shroom", "Drink to increase maximum health", px, py, 1) {
	this->iStrength = strength;
}

bool cItem_MaxHealthPotion::OnInteraction(Dynamic* dynamic) {
	OnUse(dynamic);
	return true; // Add to the inventory
}

void cItem_MaxHealthPotion::OnUse(Dynamic* dynamic) {
	((Creature*)dynamic)->increaseMaxHealth(this->iStrength);
}
