#pragma once
using namespace std;
#include<string>
#include <SFML/Graphics.hpp>
#include <iostream>

class Entity {
protected:
	float px, py;
	float width, height;
	string name;
public:
	Entity();
	Entity(string name, float px, float py);
	//~Entity();
	void setDimensions(float width, float height);

	void setPartialTexture(int px, int py, int dx, int dy);
	void draw(sf::RenderWindow* window);

	// Getters
	inline float getPosX() { return this->px; }
	inline float getPosY() { return this->py; }
	inline void setPosX(float px) { this->px = px; }
	inline void setPosY(float py) { this->py = py; }
	inline float getWidth() { return this->width; }
	inline float getHeight() { return this->height; }
	inline string getName() { return this->name; }

protected:
	sf::RectangleShape shape;
};