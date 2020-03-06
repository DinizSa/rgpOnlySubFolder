#include "assets.h"

Assets::Assets() {
	mapSizeSprite["MapBlock"] = 34;
	mapSizeSprite["RespectableDistance"] = 34;
	mapSizeSprite["EarthBender"] = 34;
	mapSizeSprite["PackMan"] = 34;
	mapSizeSprite["FireLady"] = 34;
	mapSizeSprite["RedFlowers"] = 34;
	mapSizeSprite["Portal"] = 34;
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


	// B&W
	load("MapWildOne", "assets/tiles/MapWildOneBW.png");
	load("MapWildOneTrip", "assets/tiles/MapWildOneTripBW.png");
	load("EarthBender", "assets/tiles/EarthBender4BW.png");
	load("FireLady", "assets/tiles/FireLady4BW.png");
	load("PackMan", "assets/tiles/PackMan4BW.png");
	load("RedFlowers", "assets/tiles/RedFlowersBW.png");
	load("Portal", "assets/tiles/PortalBWY.png");

}


void Assets::LoadDynamicMaps() {

	auto load = [&](cDynamicMap* dynMap) {
		m_dynamicMaps[dynMap->getName()] = dynMap;
	};

	load(new cDynamicMap_One);
	load(new cDynamicMap_OneTrip);

}