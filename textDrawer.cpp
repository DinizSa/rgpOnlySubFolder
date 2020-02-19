#include "textDrawer.h"

cTextDrawer::cTextDrawer(){
	if (!font.loadFromFile("assets/fonts/JandaManateeSolid.ttf"))
		cout << "Error loading Font!" << endl;
	this->text.setFont(font);
	this->text.setFillColor(sf::Color::Red);
	this->text.setPosition(300.f, 20.f);
}

cTextDrawer::~cTextDrawer() {
}

cTextDrawer::cTextDrawer(string text) {
	if (!font.loadFromFile("assets/fonts/JandaManateeSolid.ttf"))
		cout << "Error loading Font!" << endl;
	this->text.setFont(font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::Red);
	this->text.setPosition(300.f, 20.f);
}

void cTextDrawer::setText(string text) {
	this->text.setString(text);
}

void cTextDrawer::drawText(sf::RenderWindow* window) {
	window->draw(text);
}

