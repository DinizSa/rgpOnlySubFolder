#include "textDrawer.h"

cTextDrawer::cTextDrawer(){
	if (!font.loadFromFile("assets/fonts/JandaManateeSolid.ttf"))
		cout << "Error loading Font!" << endl;
	// Dialogue
	sfDialogue.setFont(font);
	sfDialogue.setPosition(50.f, 535.f);
	//sfDialogue.setOutlineColor({ 0,0,0,128 });
	// Background of dialogue
	sfRectText.setFillColor({ 0,0,0,0 });
	sfRectText.setPosition(0.f, 500.f);
	sfRectText.setSize(sf::Vector2f(800.f, 100.f));
	// Health
	sfHealth.setFont(font);
	sfHealth.setPosition(600.f,40.f);
	sfHealth.setFillColor(sf::Color::Color({ 230,30,30,255}));

	//// Inventory
	// Title
	sfMode.setFont(font);
	sfMode.setPosition(320.f,30.f);
	sfMode.setFillColor(sf::Color::Color({ 220,30,30,255}));
	// Name
	sfItemName.setFont(font);
	sfItemName.setString("");
	sfItemName.setCharacterSize(20);
	sfItemName.setPosition(400.f,100.f);
	sfItemName.setFillColor(sf::Color::White);
	// Quantity
	sfItemQuantity.setFont(font);
	sfItemQuantity.setString("");
	sfItemQuantity.setCharacterSize(20);
	sfItemQuantity.setPosition(400.f, 200.f);
	sfItemQuantity.setFillColor(sf::Color::White);
	// Description
	sfItemDescription.setFont(font);
	sfItemDescription.setString("");
	sfItemDescription.setCharacterSize(20);
	sfItemDescription.setPosition(400.f,300.f);
	sfItemDescription.setFillColor(sf::Color::White);
}

cTextDrawer::~cTextDrawer() {
}

// Local map mode
void cTextDrawer::setHealth(int health, int maxHealth) {
	sfHealth.setString(to_string(health) + "/" + to_string(maxHealth) + " HP");
}
void cTextDrawer::setDialogue(string text, sf::Color color) {
	sfDialogue.setString(text);
	sfDialogue.setFillColor(sf::Color::White);
	// Background of dialogue
	sfRectText.setFillColor({ 20,20,20,155 });
}

void cTextDrawer::removeDialogue() {
	sfDialogue.setString("");
	sfRectText.setFillColor({ 0,0,0,0 });
}
void cTextDrawer::drawText_MapMode(sf::RenderWindow* pWindow) {
	pWindow->draw(sfRectText);
	pWindow->draw(sfDialogue);
	pWindow->draw(sfHealth);
}

// Inventory mode
void cTextDrawer::setItemText(string name, int quantity, string description) {
	sfItemName.setString("ITEM: \n" + name); 
	sfItemQuantity.setString("QUANTITY: \n" + to_string(quantity));
	sfItemDescription.setString("DESCRIPTION: \n" + description);
}
void cTextDrawer::setNoItemText() {
	sfItemName.setString("You dont have any item!"); 
	sfItemQuantity.setString("");
	sfItemDescription.setString("");
}
void cTextDrawer::drawText_InventaryMode(sf::RenderWindow* window) {
	window->draw(sfMode); 
	window->draw(sfItemName); 
	window->draw(sfItemQuantity);
	window->draw(sfItemDescription); 
}
