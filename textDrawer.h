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
	void setDialogue(string text, sf::Color color);
	void removeDialogue();
	void setHealth(int health);

private:
	sf::Font font;
	sf::Text sfDialogue;
	sf::Text sfHealth;
	cTextDrawer();
	~cTextDrawer();
};