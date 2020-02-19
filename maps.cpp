#include "maps.h"
#include "assets.h"
#include <iostream>
#include <fstream>

Maps::Maps(string pathToMap, string spriteAsset, int bgWidth, int bgHeight) {

	// Read map and settings from file and construct an array of landscapes
	ifstream data(pathToMap, ios::in | ios::binary);
	if (data.is_open()) {
		int spriteDimX, spriteDimY, spriteNrX, spriteNrY;
		data >> spriteAsset >> nrHorizontal >> nrVertical >> spriteDimX >> spriteDimY >> spriteNrX >> spriteNrY;
		landscapes = new Landscape[nrHorizontal * nrVertical];
		indicesMap = new int[nrHorizontal * nrVertical];
		solidMap = new bool[nrHorizontal * nrVertical];

		int widthLandscape = bgWidth / nrHorizontal;
		int heightLandscape = bgHeight / nrVertical;
		int widthSpriteInd = spriteDimX / spriteNrX;
		int heightSpriteInd = spriteDimY / spriteNrY;

		for (int y = 0; y < nrVertical ; y++)
		{
			for (int x = 0; x < nrHorizontal; x++)
			{
				int ind = x + y * nrHorizontal;
				data >> indicesMap[ind] >> solidMap[ind];
				landscapes[ind] = Landscape(spriteAsset, x * widthLandscape, y * heightLandscape, widthLandscape, heightLandscape);
				int posSpriteX = ((int)indicesMap[ind] % spriteNrX) * widthSpriteInd;
				int posSpriteY = floor(indicesMap[ind] / spriteNrX) * heightSpriteInd;
				landscapes[ind].setPartialTexture(posSpriteX, posSpriteY, widthSpriteInd, heightSpriteInd);
			}
		}
	}
}

bool Maps::getSolid(int x, int y) {
	return solidMap[x + nrHorizontal * y];
}

Maps::~Maps() {
	delete[] landscapes;
	delete[] indicesMap;
	delete[] solidMap;
}

void Maps::draw(sf::RenderWindow* window) {
	for (int i = 0; i < nrHorizontal * nrVertical; i++)
	{
		//if(solidMap[i])
			landscapes[i].draw(window);
	}
}
