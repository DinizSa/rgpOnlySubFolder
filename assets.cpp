#include "assets.h"

Assets::Assets() {
	mapSizeSprite["MapBlock"] = 34;
	mapSizeSprite["RespectableDistance"] = 34;
	mapSizeSprite["EarthBender"] = 34;
	mapSizeSprite["PackMan"] = 34;
	mapSizeSprite["FireLady"] = 34;
	mapSizeSprite["RedFlowers"] = 34;
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
	load("MapWildOne", "assets/tiles/MapWildOne.png");
	load("MapWildOneTrip", "assets/tiles/MapWildOneTrip.png");
	load("Bandido", "assets/tiles/Bandido.png");
	load("Coelho", "assets/tiles/Coelho.png");

	load("EarthBender", "assets/tiles/EarthBender4.png");
	load("FireLady", "assets/tiles/FireLady4.png");
	load("PackMan", "assets/tiles/PackMan4.png");
	load("RedFlowers", "assets/tiles/RedFlowers.png");

	
}


void Assets::LoadMaps() {

	auto load = [&](Maps* map) {
		m_mapsMaps[map->getName()] = map;
	};

	load(new Maps_WildOne());
	load(new Maps_WildOneTrip());

}