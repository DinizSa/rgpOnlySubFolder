#include "assets.h"

Assets::Assets() {
	mapSizeSprite["MapBlock"] = 34;
	mapSizeSprite["RespectableDistance"] = mapSizeSprite["MapBlock"] + 20;
	mapSizeSprite["EarthBender"] = 34;
	mapSizeSprite["FireLady"] = 34;
}

Assets::~Assets() {

}

void Assets::LoadTextures() {
	auto load = [&](string sName, string sFileName) {
		sf::Texture texture;
		texture.loadFromFile(sFileName);
		m_mapsTextures[sName] = texture;
	};

	// Load assets
	//load("tileCharacters", "assets/tiles/tileCharacters.png");
	load("Map", "assets/tiles/tileMap.png");
	load("Bandido", "assets/tiles/Bandido.png");
	load("Coelho", "assets/tiles/Coelho.png");

	load("EarthBender", "assets/tiles/tileEarthBender4.png");
	load("FireLady", "assets/tiles/FireLady4.png");
	//load("FireLady", "assets/tiles/tileFireLady.png");
	load("PackMan", "assets/tiles/tilePackMan.png");
	load("UnpackMan", "assets/tiles/tileUnpackMan.png");
	load("Rabbit", "assets/tiles/tileRabbit.png");

	
}
