#include "textDrawer.h"
#include "constants.h"

cTextDrawer::cTextDrawer(){
	if (!font.loadFromFile("assets/fonts/JandaManateeSolid.ttf"))
		cout << "Error loading Font!" << endl;
	// Dialogue
	sfDialogue.setFont(font);
	//sfDialogue.setPosition(50.f, 535.f);
	//sfDialogue.setOutlineColor({ 0,0,0,128 });
	// Background of dialogue
	sfRectText.setFillColor({ 0,0,0,0 });
	sfRectText.setSize(sf::Vector2f(constants::VIEW_WIDTH, 100.f));
	// Health
	sfHealth.setFont(font);
	sfHealth.setFillColor(sf::Color::Color({ 225,30,30,255}));
	sfHealth.setCharacterSize(25);

	//// Inventory
	// Title
	sfMode.setFont(font);
	sfMode.setPosition(constants::VIEW_WIDTH / 2 - 50,30.f);
	sfMode.setFillColor(sf::Color::Color({ 225,30,30,255}));
	// Name
	sfItemName.setFont(font);
	sfItemName.setString("");
	sfItemName.setCharacterSize(25);
	sfItemName.setPosition(constants::VIEW_WIDTH / 2,100.f);
	sfItemName.setFillColor(sf::Color::White);
	// Quantity
	sfItemQuantity.setFont(font);
	sfItemQuantity.setString("");
	sfItemQuantity.setCharacterSize(25);
	sfItemQuantity.setPosition(constants::VIEW_WIDTH / 2, 200.f);
	sfItemQuantity.setFillColor(sf::Color::White);
	// Description
	sfItemDescription.setFont(font);
	sfItemDescription.setString("");
	sfItemDescription.setCharacterSize(25);
	sfItemDescription.setPosition(constants::VIEW_WIDTH / 2,300.f);
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
	float viewOriginX = pWindow->getView().getCenter().x - constants::VIEW_WIDTH / 2;
	float viewOriginY = pWindow->getView().getCenter().y - constants::VIEW_HEIGHT / 2;
	sfRectText.setPosition(viewOriginX, viewOriginY + constants::VIEW_HEIGHT - sfRectText.getSize().y);
	pWindow->draw(sfRectText);
	sfDialogue.setPosition(viewOriginX + 50, viewOriginY + constants::VIEW_HEIGHT - 65);
	pWindow->draw(sfDialogue);
	sfHealth.setPosition(viewOriginX - 150, viewOriginY + 20.f);
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
