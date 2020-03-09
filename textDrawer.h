#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
#include <string>
#include <iostream>

class cTextDrawer {
public:

	static cTextDrawer& get() {
		static cTextDrawer me;
		return me;
	}
	cTextDrawer(cTextDrawer&) = delete;
	void operator = (cTextDrawer&) = delete;

	void drawText(sf::RenderWindow* window);
	void setText(string text, sf::Color color);
	void removeText();

private:
	sf::Font font;
	sf::Text sfText;
	cTextDrawer();
	~cTextDrawer();
};