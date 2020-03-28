#pragma once
#include "item.h"
#include <vector>

class cInventory {
public:
	cInventory();
	void update();
	void update(vector<cItem*>* items);
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