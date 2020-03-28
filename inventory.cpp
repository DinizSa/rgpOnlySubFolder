#include "inventory.h"

cInventory::cInventory() {
	this->indiceItem = -1;
	this->nrItemsLine = 0;
	this->sizeInventory = 0;
	this->vInventory = nullptr;
};

void cInventory::update(vector<cItem*>* items) {
	this->vInventory = items;
	if (vInventory->size() < 1)
		this->indiceItem = -1;
	else
		this->indiceItem = 0;

	// Format items
	nrItemsLine = 6;
	this->sizeInventory = (*vInventory).size();
	int counter = 0;
	for (auto item : (*vInventory)) {
		item->setDimensions(80.f, 80.f);
		item->updatePosition((counter % nrItemsLine) * 100 + 10, (floor(counter / nrItemsLine) * 100 + 100));
		counter++;
	}
}

void cInventory::draw(sf::RenderWindow& pWindow) {
	for (int i = 0; i < (*vInventory).size();i++) {
		(*vInventory)[i]->draw(&pWindow);
		if (i == this->indiceItem)
			(*vInventory)[i]->drawBorder(&pWindow);
	}
}

void cInventory::handleInputs(sf::Event event) {
	if (event.key.code == sf::Keyboard::A && this->indiceItem != 0)
		this->indiceItem--;
	if (event.key.code == sf::Keyboard::D && this->indiceItem < this->sizeInventory-1)
		this->indiceItem++;
	if (event.key.code == sf::Keyboard::W && this->indiceItem > this->nrItemsLine-1)
		this->indiceItem -= nrItemsLine;
	if (event.key.code == sf::Keyboard::S && this->indiceItem + this->nrItemsLine < this->sizeInventory)
		this->indiceItem += nrItemsLine;
	if (event.key.code == sf::Keyboard::Space) { // Consumes one it
		(*vInventory)[this->indiceItem]->updateQuantity(-1);
	}
}