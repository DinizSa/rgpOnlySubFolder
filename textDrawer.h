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
	void setText(string name, string text, sf::Color color);
	void removeText(string name);

private:
	sf::Font font;
	map<string, sf::Text> _mapTexts;
};