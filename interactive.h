#pragma once
#include "dynamic.h"

class Interactive : public Dynamic {
public:
	Interactive();
	Interactive(string name, float px, float py, float width, float height);
	~Interactive();
};