#pragma once
#include "entity.h"

class Landscape: public Entity {
public:
	Landscape();
	Landscape(string name, float px, float py, float width, float height);
	~Landscape();
};