#pragma once
#include "landscape.h"

class Maps {
public:
	Maps(string sName);
	~Maps();
	void draw(sf::RenderWindow* window, float playerVx, float playerVy);
	bool getSolid(int x, int y);
	inline int getNrHorizontal() { return nrHorizontal; }
	inline int getNrVertical() { return nrVertical; }
	inline string getName() { return sName; }
	void setBackground(string asset, float backgroundWidth, float backgroundHeight, float playerX, float playerY);

private:
	Landscape* landscapes;
	int* indicesMap;
	bool* solidMap;
	int nrHorizontal, nrVertical;
	string sName;
	Landscape background;
	bool bInitialized;

};
