#include "textDrawer.h"

cTextDrawer::cTextDrawer(){
}

cTextDrawer::~cTextDrawer() {
}

void cTextDrawer::setText(string name, string text, sf::Color color) {
	if (!font.loadFromFile("assets/fonts/JandaManateeSolid.ttf"))
		cout << "Error loading Font!" << endl;
	sf::Text sfText;
	sfText.setString(text);
	sfText.setFont(font);
	sfText.setFillColor(color);
	sfText.setPosition(300.f, 20.f);
	sfText.setOutlineColor({ 0,0,0,128 });
	_mapTexts[name] = sfText;
}

void cTextDrawer::removeText(string name) {
	_mapTexts.erase(name);
}

void cTextDrawer::drawText(sf::RenderWindow* window) {
	for(auto text : _mapTexts)
		window->draw(text.second);
}

