#include "textDrawer.h"

cTextDrawer::cTextDrawer(){
}

cTextDrawer::~cTextDrawer() {
}

void cTextDrawer::setText(string text, sf::Color color) {
	if (!font.loadFromFile("assets/fonts/JandaManateeSolid.ttf"))
		cout << "Error loading Font!" << endl;
	sfText.setString(text);
	sfText.setFont(font);
	sfText.setFillColor(color);
	sfText.setPosition(120.f, 20.f);
	sfText.setOutlineColor({ 0,0,0,128 });
}

void cTextDrawer::removeText() {
	sfText.setString("");
}

void cTextDrawer::drawText(sf::RenderWindow* pWindow) {
	pWindow->draw(sfText);
}

