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

	void drawText_MapMode(sf::RenderWindow* window);
	inline void drawText_InventaryMode(sf::RenderWindow* window) { window->draw(sfTitle); }
	void setDialogue(string text, sf::Color color);
	void removeDialogue();
	void setHealth(int health, int maxHealth);
	inline void setTitle(string title) { sfTitle.setString(title); }

private:
	sf::Font font;
	sf::Text sfDialogue;
	sf::Text sfHealth;
	sf::Text sfTitle;
	cTextDrawer();
	~cTextDrawer();
};