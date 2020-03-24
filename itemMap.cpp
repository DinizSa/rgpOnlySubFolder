#include "itemMap.h";
#include "creature.h"

cItemMap::cItemMap(string name, string asset, string desc, float px, float py, int iQuantity): Dynamic(name, asset, px, py, true, true, true, true, 1.f) {
	this->sName = name;
	this->sAsset = asset;
	this->sDesc = desc;
	this->iQuantity = iQuantity;
}


// <------------------------------------------ Health Potion Item ------------------------------------------>
cItemMap_HealthPotion::cItemMap_HealthPotion(int strength):cItemMap("Health Potion", "hearth", "Drink to regenerate health", -1, -1,1) {
	this->iStrength = strength;
}

cItemMap_HealthPotion::cItemMap_HealthPotion(int strength, float px, float py): cItemMap("Health Potion", "hearth", "Drink to regenerate health", px, py, 1) {
	this->iStrength = strength;
}

bool cItemMap_HealthPotion::OnInteraction(Dynamic* dynamic) {
	OnUse(dynamic);
	return false;
}

void cItemMap_HealthPotion::OnUse(Dynamic* dynamic) {
	((Creature*)dynamic)->heal(this->iStrength);
}
