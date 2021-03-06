#pragma once
using namespace std;
#include<string>
#include <SFML/Graphics.hpp>
#include <iostream>

class Entity {
protected:
	float px, py;
	float width, height;
	string sAsset;
public:
	Entity();
	Entity(string sAsset, float px, float py);
	//~Entity();
	void setDimensions(float width, float height);

	void setPartialTexture(int px, int py, int dx, int dy);
	void setDeathFilter();
	void setInjuredFilter();
	void setMaskedFilter(string asset);
	void resetFilters();
	void updatePosition(float px, float py);
	void draw(sf::RenderWindow* window);

	// Getters
	inline float getPosX() { return this->px; }
	inline float getPosY() { return this->py; }
	inline void setPosX(float px) { this->px = px; this->shape.setPosition(sf::Vector2f(px, py)); }
	inline void setPosY(float py) { this->py = py; this->shape.setPosition(sf::Vector2f(px, py));}
	inline float getWidth() { return this->width; }
	inline float getHeight() { return this->height; }
	inline string getAssetName() { return this->sAsset; }
	

protected:
	sf::RectangleShape shape;
};