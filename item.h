#pragma once
#include <memory>
#include "dynamic.h"

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

// <------------------------------------------ Health Potion Item -> Heal ------------------------------------------>
class cItem_HealthPotion : public cItem {
public:
	cItem_HealthPotion(int strength); 
	cItem_HealthPotion(int strength, float px, float py); 
	bool OnInteraction(Dynamic* dynamic) override;
	void OnUse(Dynamic* dynamic) override;

};

// <------------------------------------------ Max Health Potion Item -> Incleases Max Health ------------------------------------------>
class cItem_MaxHealthPotion : public cItem {
public:
	cItem_MaxHealthPotion(int strength); 
	cItem_MaxHealthPotion(int strength, float px, float py); 
	bool OnInteraction(Dynamic* dynamic) override;
	void OnUse(Dynamic* dynamic) override;
};

// <------------------------------------------ Scroll of bandidos truth ------------------------------------------>
class cItem_ScrollBandidosTruth : public cItem {
public:
	cItem_ScrollBandidosTruth();
	cItem_ScrollBandidosTruth(float px, float py);
	bool OnInteraction(Dynamic* dynamic) override;
	void OnUse(Dynamic* dynamic) override;
};