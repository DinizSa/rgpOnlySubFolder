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
	for (auto dynMaps : m_dynamicMaps)
		delete dynMaps.second;
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


//void Assets::LoadMaps() {
//
//	auto load = [&](Maps* map) {
//		m_maps[map->getName()] = map;
//	};
//
//	load(new Maps("MapWildOne"));
//	load(new Maps("MapWildOneTrip"));
//
//}

void Assets::LoadDynamicMaps() {

	auto load = [&](cDynamicMap* dynMap) {
		m_dynamicMaps[dynMap->getName()] = dynMap;
	};

	load(new cDynamicMap_One);
	load(new cDynamicMap_OneTrip);

}