#include "landscape.h"

Landscape::Landscape():
	Entity() {

}

Landscape::Landscape(string name, float px, float py, float width, float height) :
	Entity(name, px, py) {
	this->setDimensions(width, height);

}

Landscape::~Landscape() {

}