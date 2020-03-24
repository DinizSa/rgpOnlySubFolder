#pragma once
#include <memory>
#include "dynamic.h"

class cItemMap : public Dynamic {
public:
	cItemMap(string name, string asset, string desc, float px, float py, int iQuantity);
	virtual bool OnInteraction(Dynamic* dynamic)=0;
	virtual void OnUse(Dynamic* dynamic)=0;

	// Getters && Setters
	inline string getName() { return sName; };
	inline string getAsset() { return sAsset; };
	inline string getDescription() { return sDesc; };
protected:
	int iQuantity;
	string sName;
	string sAsset;
	string sDesc;
};

// <------------------------------------------ Health Potion Item ------------------------------------------>
class cItemMap_HealthPotion : public cItemMap {
public:
	cItemMap_HealthPotion(int strength); // To put in the characters
	cItemMap_HealthPotion(int strength, float px, float py); // to put in the map
	bool OnInteraction(Dynamic* dynamic) override;
	void OnUse(Dynamic* dynamic) override;

private:
	int iStrength;
};