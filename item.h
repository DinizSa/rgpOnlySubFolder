#pragma once
#include <memory>
#include "dynamic.h"
#include "projectile.h"

class cItem : public Dynamic {
public:
	cItem(string name, string asset, string desc, float px, float py, int iQuantity, bool consumable);
	virtual bool OnInteraction(Dynamic* dynamic)=0;
	virtual void OnUse(Dynamic* dynamic)=0;

	// Getters && Setters
	inline string getName() { return sName; };
	inline string getAsset() { return sAsset; };
	inline string getDescription() { return sDesc; };
	inline int getStrength() { return this->iStrength; };
	inline int isConsumable() { return this->consumable; };
	inline int getQuantity() { return iQuantity; };
	bool updateQuantity(int quantity);
	void drawBorder(sf::RenderWindow* pWindow);

protected:
	int iQuantity;
	string sName;
	string sAsset;
	string sDesc;
	int iStrength;
	bool consumable;
};

// <------------------------------------------ Health Potion Item ------------------------------------------>
class cItem_HealthPotion : public cItem {
public:
	cItem_HealthPotion(int strength); 
	cItem_HealthPotion(int strength, float px, float py); 
	bool OnInteraction(Dynamic* dynamic) override;
	void OnUse(Dynamic* dynamic) override;

};

// <------------------------------------------ Max Health Potion Item ------------------------------------------>
class cItem_MaxHealthPotion : public cItem {
public:
	cItem_MaxHealthPotion(int strength); 
	cItem_MaxHealthPotion(int strength, float px, float py); 
	bool OnInteraction(Dynamic* dynamic) override;
	void OnUse(Dynamic* dynamic) override;
};

// <------------------------------------------ Scroll of gustavus ------------------------------------------>
class cItem_Scroll : public cItem {
public:
	cItem_Scroll();
	cItem_Scroll(float px, float py);
	bool OnInteraction(Dynamic* dynamic) override;
	void OnUse(Dynamic* dynamic) override;
};
// <------------------------------------------ Calcetine sock ------------------------------------------>
class cItem_Calcetine : public cItem {
public:
	cItem_Calcetine();
	cItem_Calcetine(float px, float py);
	bool OnInteraction(Dynamic* dynamic) override;
	void OnUse(Dynamic* dynamic) override;
};

// <------------------------------------------ Weapon ------------------------------------------>
class cItem_Weapon : public cItem {
public:
	cItem_Weapon(string name, string asset, string description, int strength);
	cItem_Weapon(string name, string asset, string description, int strength, float px, float py);
	bool OnInteraction(Dynamic* dynamic) override;
	inline void OnUse(Dynamic* dynamic) override {};
	virtual cProjectile* OnWeaponUse(Dynamic* dynamic)=0;

};
// <------------------------------------------ Sword item ------------------------------------------>
class cItem_Sword : public cItem_Weapon {
public:
	cItem_Sword(int strength);
	cItem_Sword(int strength, float px, float py);
	bool OnInteraction(Dynamic* dynamic) override;
	cProjectile* OnWeaponUse(Dynamic* dynamic) override;
};