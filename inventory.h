#pragma once
#include "item.h"
#include <vector>

class cInventory {
public:
	cInventory(vector<cItem*>* items);
	void repositionElements();
	cItem* handleInputs(sf::Event event);
	void draw(sf::RenderWindow& pWindow);

	// Setters and
	cItem* getSelectedItem();
private:
	int nrItemsLine;
	int indiceSelected;
	vector<cItem*>* vInventory;
	float widthItem;
	float marginItem;
};