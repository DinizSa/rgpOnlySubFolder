#include "maps.h"
#include "assets.h"
#include <iostream>
#include <fstream>
#include "constants.h"

Maps::Maps(string sName) {
	bInitialized = false;
	int assetsSize = Assets::get().GetSizeSprite();
	// Read map and settings from file and construct an array of landscapes
	this->sName = sName;
	ifstream data(sName + ".txt", ios::in | ios::binary);
	if (data.is_open()) {
		int spriteDimX, spriteDimY, spriteNrX, spriteNrY;
		string spriteAsset;
		data >> spriteAsset >> nrHorizontal >> nrVertical >> spriteDimX >> spriteDimY >> spriteNrX >> spriteNrY;
		landscapes = new Landscape[nrHorizontal * nrVertical];
		indicesMap = new int[nrHorizontal * nrVertical];
		solidMap = new bool[nrHorizontal * nrVertical];
		const int factorBg = 1.5;
		int bgWidth = constants::ASSET_SIZE * nrHorizontal* factorBg;
		int bgHeight = constants::ASSET_SIZE * nrVertical* factorBg;
		

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
				landscapes[ind] = Landscape(spriteAsset, x * assetsSize, y * assetsSize, (float)assetsSize, (float)assetsSize);
				int posSpriteX = ((int)indicesMap[ind] % spriteNrX) * widthSpriteInd;
				int posSpriteY = floor(indicesMap[ind] / spriteNrX) * heightSpriteInd;
				landscapes[ind].setPartialTexture(posSpriteX, posSpriteY, widthSpriteInd, heightSpriteInd);
			}
		}

	}
}

void Maps::setBackground(float playerX, float playerY) {
	// Background
	const int backgroundW = 1024;
	const int backgroundH = 1024;
	const float backgroundPosX = playerX - backgroundW / 2;
	const float backgroundPosY = playerY - backgroundH / 2;
	background = Landscape("bgpSunset", backgroundPosX, backgroundPosY, backgroundW, backgroundH);
	background.setPosX(backgroundPosX);
	background.setPosY(backgroundPosY);
}

bool Maps::getSolid(int x, int y) {
	return solidMap[x + nrHorizontal * y];
}

Maps::~Maps() {
	delete[] landscapes;
	delete[] indicesMap;
	delete[] solidMap;
}

void Maps::draw(sf::RenderWindow* window, float playerVx, float playerVy) {
	const float speedParalax = 3;
	background.setPosX(background.getPosX() + playerVx / speedParalax);
	background.setPosY(background.getPosY() + playerVy / speedParalax);

	background.draw(window);
	for (int i = 0; i < nrHorizontal * nrVertical; i++)
		landscapes[i].draw(window);
	
}
