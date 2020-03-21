#include "entity.h"
#include "assets.h"

Entity::Entity() {
	this->px = 0.f;
	this->py = 0.f;
	this->width = 0.f;
	this->height = 0.f;
	this->sAsset = "";
	this->shape = sf::RectangleShape(sf::Vector2f(width, height));
}

Entity::Entity(string sAsset, float px, float py) {
	this->sAsset = sAsset;
	this->px = px;
	this->py = py;
	this->width = 34;
	this->height = 34;
	this->shape = sf::RectangleShape(sf::Vector2f(width, height));
	this->shape.setPosition(sf::Vector2f(px, py));
	this->shape.setTexture(&Assets::get().GetTexture(sAsset));
}

void Entity::setPartialTexture(int px, int py, int dx, int dy) {
	this->shape.setTextureRect(sf::IntRect(px, py, dx, dy));
}

void Entity::setDimensions(float width, float height) { 
	this->width = width; this->height = height;
	this->shape.setSize(sf::Vector2f(width, height));
}


//Entity::~Entity() {
//}

void Entity::draw(sf::RenderWindow* window) {
	window->draw(this->shape);
}