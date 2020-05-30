#include "entity.h"
#include "assets.h"
#include "constants.h"

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
	this->px = px * constants::ASSET_SIZE;
	this->py = py * constants::ASSET_SIZE;
	this->width = Assets::get().GetSizeSprite();
	this->height = Assets::get().GetSizeSprite();
	this->shape = sf::RectangleShape(sf::Vector2f(width, height));
	this->shape.setPosition(sf::Vector2f(px, py));
	this->shape.setTexture(&Assets::get().GetTexture(sAsset));
}



void Entity::setPartialTexture(int px, int py, int dx, int dy) {
	this->shape.setTextureRect(sf::IntRect(px, py, dx, dy));
}
void Entity::setDeathFilter() {
	this->shape.setFillColor(sf::Color::Color(20,20,20,100));
}
void Entity::setInjuredFilter() {
	this->shape.setFillColor(sf::Color::Color(220,10,10,150));
}
void Entity::resetFilters() {
	this->shape.setFillColor(sf::Color::Color(255, 255, 255, 255));
}

void Entity::updatePosition(float px, float py) {
	setPosX(px);
	setPosY(py);
	this->shape.setPosition(sf::Vector2f(this->getPosX(), this->getPosY()));
}

void Entity::setDimensions(float width, float height) { 
	this->width = width; 
	this->height = height;
	this->shape.setSize(sf::Vector2f(width, height));
}


//Entity::~Entity() {
//}

void Entity::draw(sf::RenderWindow* window) {
	//this->shape.setOutlineThickness(1.f);
	//this->shape.setOutlineColor(sf::Color::White);
	window->draw(this->shape);
}