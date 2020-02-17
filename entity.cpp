#include "entity.h"
#include "assets.h"

Entity::Entity() {
	this->px = 0.f;
	this->py = 0.f;
	this->width = 0.f;
	this->height = 0.f;
	this->name = "";
	this->shape = sf::RectangleShape(sf::Vector2f(width, height));
}

Entity::Entity(string name, float px, float py, float width, float height) {
	this->name = name;
	this->px = px;
	this->py = py;
	this->width = width;
	this->height = height;
	this->shape = sf::RectangleShape(sf::Vector2f(width, height));
	this->shape.setPosition(sf::Vector2f(px, py));
	this->shape.setTexture(&Assets::get().GetTexture(this->getName()));
}

void Entity::setPartialTexture(int px, int py, int dx, int dy) {
	this->shape.setTextureRect(sf::IntRect(px, py, dx, dy));
}


Entity::~Entity() {
}

void Entity::draw(sf::RenderWindow* window) {
	window->draw(this->shape);
}