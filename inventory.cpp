#include "inventory.h"
#include "textDrawer.h"

cInventory::cInventory() {
	this->indiceSelected = -1; // set invalid index
	this->nrItemsLine = 4;
	this->widthItem = 100.f;
	this->marginItem = 10.f;
	this->vInventory = nullptr;
};

void cInventory::update(vector<cItem*>* items) {
	this->vInventory = items;

	// Limits current indice
	if ((*vInventory).size() < 1)
		this->indiceSelected = -1;
	else if (this->indiceSelected < 0)
		this->indiceSelected = 0;
	if (this->indiceSelected > (*vInventory).size() - 1)
		this->indiceSelected = (*vInventory).size() - 1;

	// Format items
	for (unsigned i = 0; i < (*vInventory).size(); i++) {
		(*vInventory)[i]->setDimensions(this->widthItem- this->marginItem*2, this->widthItem - this->marginItem * 2);
		(*vInventory)[i]->updatePosition((i % nrItemsLine) * this->widthItem + this->marginItem, (floor(i / nrItemsLine) * this->widthItem + 100));
	}
}

void cInventory::draw(sf::RenderWindow& pWindow) {
	for (int i = 0; i < (*vInventory).size();i++) { // Draw each item
		(*vInventory)[i]->draw(&pWindow);
		if (i == this->indiceSelected) // Border on selected item
			(*vInventory)[i]->drawBorder(&pWindow);
	}
}

cItem* cInventory::getSelectedItem() {
	if (this->indiceSelected > -1 && this->indiceSelected < vInventory->size()) {
		return (*vInventory)[this->indiceSelected];
	}
	return nullptr;
}

// Returns an item if his quantity changes
cItem* cInventory::handleInputs(sf::Event event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::A && this->indiceSelected != 0)
			this->indiceSelected--;
		if (event.key.code == sf::Keyboard::D && this->indiceSelected < (*vInventory).size() - 1)
			this->indiceSelected++;
		if (event.key.code == sf::Keyboard::W && this->indiceSelected > this->nrItemsLine - 1)
			this->indiceSelected -= nrItemsLine;
		if (event.key.code == sf::Keyboard::S && this->indiceSelected + this->nrItemsLine < (*vInventory).size())
			this->indiceSelected += nrItemsLine;
		if (event.key.code == sf::Keyboard::Space && !this->vInventory->empty()) { // Consumes it
			if (!(*vInventory)[this->indiceSelected]->updateQuantity(-1)) // Droped to 0 ?
				return (*vInventory)[this->indiceSelected];
		}
	}
	return nullptr;
}