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

	// Map mode
	void drawText_MapMode(sf::RenderWindow* window);
	void setDialogue(string text, sf::Color color);
	void removeDialogue();
	void setHealth(int health, int maxHealth);

	// Inventary
	void drawText_InventaryMode(sf::RenderWindow* window);
	inline void setTitleMode(string title) { sfMode.setString(title); }
	void setItemText(string name, int quantity, string description);
	void setNoItemText();

private:
	sf::Font font;

	// Map mode
	sf::Text sfDialogue;
	sf::Text sfHealth;
	// Inventary
	sf::Text sfMode;
	sf::Text sfItemName;
	sf::Text sfItemQuantity;
	sf::Text sfItemDescription;

	cTextDrawer();
	~cTextDrawer();
};