#pragma once
#include "SFML/Graphics.hpp"
#include "interactive.h"

class InputHandler {
public:
	InputHandler();
	~InputHandler(); 
	void pollEvents(sf::RenderWindow* window, vector<Dynamic*>* vDynamic, Dynamic* controlled);

private:
	bool bPressedUp, bPressedRight, bPressedDown, bPressedLeft;
};