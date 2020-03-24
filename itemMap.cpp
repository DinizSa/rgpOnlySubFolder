#include "itemMap.h";
#include "creature.h"

cItemMap::cItemMap(shared_ptr<cItem> spItem, float px, float py, int iQuantity): Dynamic(spItem->getName(), spItem->getAsset(), px, py, true, true, true, true, 1.f) {
	this->spItem = spItem;
	this->iQuantity = iQuantity;
}

void cItemMap::OnInteraction(Dynamic* dynamic) {
	// TODO: this specific behaviours should be in the derived objects 
	dynamic->addItem(spItem, iQuantity);
	cout << spItem->getName() << " item added to the inventory of " << dynamic->getName() << endl;
}

void cItemMap::OnUse(Dynamic* dynamic) {
	cout << spItem->getName() << " item used to the inventory of " << dynamic->getName() << endl;
	((Creature*)dynamic)->heal(5);
}