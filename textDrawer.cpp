#include "textDrawer.h"

cTextDrawer::cTextDrawer(){
	if (!font.loadFromFile("assets/fonts/JandaManateeSolid.ttf"))
		cout << "Error loading Font!" << endl;
	// Dialogue
	sfDialogue.setFont(font);
	sfDialogue.setPosition(50.f, 40.f);
	sfDialogue.setOutlineColor({ 0,0,0,128 });
	// Health
	sfHealth.setFont(font);
	sfHealth.setPosition(600.f,40.f);
	sfHealth.setFillColor(sf::Color::Color({ 220,30,30,255}));
}

cTextDrawer::~cTextDrawer() {
}


void cTextDrawer::setHealth(int health, int maxHealth) {
	sfHealth.setString(to_string(health) + "/" + to_string(maxHealth) + " HP");
}


void cTextDrawer::setDialogue(string text, sf::Color color) {
	sfDialogue.setString(text);
	sfDialogue.setFillColor(color);
}

void cTextDrawer::removeDialogue() {
	sfDialogue.setString("");
}

void cTextDrawer::drawText(sf::RenderWindow* pWindow) {
	pWindow->draw(sfDialogue);
	pWindow->draw(sfHealth);
}
