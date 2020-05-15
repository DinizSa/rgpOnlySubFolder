#include "textDrawer.h"
#include "constants.h"

cTextDrawer::cTextDrawer(){
	if (!font.loadFromFile("assets/fonts/JandaManateeSolid.ttf"))
		cout << "Error loading Font!" << endl;

	int fontSizeMedium = 11;
	// Dialogue
	sfDialogue.setFont(font);
	sfDialogue.setCharacterSize(fontSizeMedium);
	sfDialogue.setFillColor(sf::Color::White);
	//sfDialogue.setPosition(50.f, 535.f);
	//sfDialogue.setOutlineColor({ 0,0,0,128 });
	// Background of dialogue
	sfRectText.setFillColor({ 0,0,0,0 });
	sfRectText.setSize(sf::Vector2f(constants::VIEW_WIDTH, constants::VIEW_HEIGHT/6));
	// Health
	sfHealth.setFont(font);
	sfHealth.setFillColor(sf::Color::Color({ 225,30,30,255}));
	sfHealth.setCharacterSize(fontSizeMedium);

	//// Inventory
	// Title
	sfMode.setFont(font);
	sfMode.setFillColor(sf::Color::Color({ 225,30,30,255}));
	sfMode.setCharacterSize(fontSizeMedium+5);
	sfMode.setPosition(30.f, 30.f);
	// Name
	sfItemName.setFont(font);
	sfItemName.setString("");
	sfItemName.setCharacterSize(fontSizeMedium);
	sfItemName.setFillColor(sf::Color::White);
	// Quantity
	sfItemQuantity.setFont(font);
	sfItemQuantity.setString("");
	sfItemQuantity.setCharacterSize(fontSizeMedium);
	sfItemQuantity.setFillColor(sf::Color::White);
	// Description
	sfItemDescription.setFont(font);
	sfItemDescription.setString("");
	sfItemDescription.setCharacterSize(fontSizeMedium);
	sfItemDescription.setFillColor(sf::Color::White);
}

cTextDrawer::~cTextDrawer() {
}

// Local map mode
void cTextDrawer::setHealth(int health, int maxHealth) {
	sfHealth.setString(to_string(health) + "/" + to_string(maxHealth) + " HP");
}
void cTextDrawer::setDialogue(string text) {
	sfDialogue.setString(text);
	// Background of dialogue 
	sfRectText.setFillColor({ 20,20,20,200 });
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
	//sfDialogue.setPosition(viewOriginX + constants::WINDOW_WIDTH / 100, viewOriginY + constants::WINDOW_HEIGHT - sfDialogue.getCharacterSize() - 5 * constants::WINDOW_HEIGHT / 100);
	sfDialogue.setPosition(viewOriginX + sfDialogue.getCharacterSize(), viewOriginY + constants::VIEW_HEIGHT - 25 - sfDialogue.getCharacterSize());
	pWindow->draw(sfDialogue);
	sfHealth.setPosition(viewOriginX + constants::VIEW_WIDTH - 100.f, viewOriginY + 10.f);
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
void cTextDrawer::drawText_InventaryMode(sf::RenderWindow* pWindow) {
	float viewMidleX = pWindow->getView().getCenter().x;
	pWindow->draw(sfMode);
	sfItemName.setPosition(viewMidleX, 100.f);
	pWindow->draw(sfItemName);
	sfItemQuantity.setPosition(viewMidleX, 150.f);
	pWindow->draw(sfItemQuantity);
	sfItemDescription.setPosition(viewMidleX, 200.f);
	pWindow->draw(sfItemDescription);
}
