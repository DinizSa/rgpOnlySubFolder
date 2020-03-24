#include "itemMap.h";
#include "creature.h"

cItemMap::cItemMap(shared_ptr<cItem> spItem, float px, float py, int iQuantity): Dynamic(spItem->getName(), spItem->getAsset(), px, py, true, true, true, true, 1.f) {
	this->spItem = spItem;
	this->iQuantity = iQuantity;
}

bool cItemMap::OnInteraction(Dynamic* dynamic) {
	// TODO: this specific behaviours should be in the derived objects 
	// ALSO: Remove from the map if interacted with. maybe oninteraction return true to remove?
	dynamic->addItem(spItem, iQuantity);
	cout << spItem->getName() << " item added to the inventory of " << dynamic->getName() << endl;
	return true;
}

void cItemMap::OnUse(Dynamic* dynamic) {
	((Creature*)dynamic)->heal(5);
	cout << spItem->getName() << " item used to the inventory of " << dynamic->getName() << endl;
}