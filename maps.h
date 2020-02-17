#pragma once
#include "landscape.h"
class Maps {
public:
	Maps(string pathToMap, string spriteAsset, int bgWidth, int bgHeight);
	~Maps();
	void draw(sf::RenderWindow* window);
	bool getSolid(int x, int y);
	inline int getNrHorizontal() { return nrHorizontal; }
	inline int getNrVertical() { return nrVertical; }

private:
	Landscape* landscapes;
	int* indicesMap;
	bool* solidMap;
	int nrHorizontal, nrVertical;
	string spriteAsset;
};