#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
#include <string>
#include <iostream>

class cTextDrawer {
public:
	cTextDrawer();
	~cTextDrawer();

	void drawText(sf::RenderWindow* window);
	void setText(string text, sf::Color color);
	void removeText();

private:
	sf::Font font;
	sf::Text sfText;
};