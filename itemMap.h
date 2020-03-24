#pragma once
#include <memory>
#include "dynamic.h"
#include "item.h"

class cItemMap : public Dynamic {
public:
	cItemMap(shared_ptr<cItem> spItem, float px, float py, int iQuantity);
	void OnInteraction(Dynamic* dynamic);
	void OnUse(Dynamic* dynamic);
protected:
	shared_ptr<cItem> spItem;
	int iQuantity;
};