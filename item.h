#pragma once
#include <memory>
#include "dynamic.h"

class cItem : public Dynamic {
public:
	cItem(string name, string asset, string desc, float px, float py, int iQuantity);
	virtual bool OnInteraction(Dynamic* dynamic)=0;
	virtual void OnUse(Dynamic* dynamic)=0;

	// Getters && Setters
	inline string getName() { return sName; };
	inline string getAsset() { return sAsset; };
	inline string getDescription() { return sDesc; };
	bool updateQuantity(int quantity);
	inline int getQuantity() { return iQuantity; };
	void drawBorder(sf::RenderWindow* pWindow);

protected:
	int iQuantity;
	string sName;
	string sAsset;
	string sDesc;
};

// <------------------------------------------ Health Potion Item -> Heal ------------------------------------------>
class cItem_HealthPotion : public cItem {
public:
	cItem_HealthPotion(int strength); 
	cItem_HealthPotion(int strength, float px, float py); 
	bool OnInteraction(Dynamic* dynamic) override;
	void OnUse(Dynamic* dynamic) override;

private:
	int iStrength;
};

// <------------------------------------------ Max Health Potion Item -> Incleases Max Health ------------------------------------------>
class cItem_MaxHealthPotion : public cItem {
public:
	cItem_MaxHealthPotion(int strength); 
	cItem_MaxHealthPotion(int strength, float px, float py); 
	bool OnInteraction(Dynamic* dynamic) override;
	void OnUse(Dynamic* dynamic) override;

private:
	int iStrength;
};