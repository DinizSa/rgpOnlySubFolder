#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
#include <string>
#include <iostream>

class cTextDrawer {
public:
	cTextDrawer();
	cTextDrawer(string text);
	~cTextDrawer();

	void drawText(sf::RenderWindow* window);
	void setText(string text);

private:
	sf::Text text;
	sf::Font font;
};