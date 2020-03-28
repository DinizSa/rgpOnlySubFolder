#pragma once
#include "item.h"
#include <vector>

class cInventory {
public:
	cInventory();
	void update(vector<cItem*>* items);
	void handleInputs(sf::Event event);
	void draw(sf::RenderWindow& pWindow);

	// Setters and
	
private:
	int sizeInventory;
	int nrItemsLine;
	int indiceItem;
	vector<cItem*>* vInventory;
};