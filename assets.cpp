#include "assets.h"

Assets::Assets() {
	mapSizeSprite["MapBlock"] = 34;
	mapSizeSprite["RespectableDistance"] = 34;
	mapSizeSprite["EarthBender"] = 34;
	mapSizeSprite["PackMan"] = 34;
	mapSizeSprite["FireLady"] = 34;
	mapSizeSprite["RedFlowers"] = 34;
	mapSizeSprite["Portal"] = 34;
	mapSizeSprite["EvilRabbit"] = 34;
	mapSizeSprite["PinkRabbit"] = 34;
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

	//load("MapWildOne", "assets/tiles/MapWildOne.png");
	//load("MapWildOneTrip", "assets/tiles/MapWildOneTrip.png");
	//load("EarthBender", "assets/tiles/EarthBender4.png");
	//load("FireLady", "assets/tiles/FireLady4.png");
	//load("PackMan", "assets/tiles/PackMan4.png");
	//load("RedFlowers", "assets/tiles/RedFlowers.png");
	//load("Portal", "assets/tiles/PortalBWY.png");
	//load("EvilRabbit", "assets/tiles/EvilRabbit.png");

	// B&W
	load("MapWildOne", "assets/tiles/MapWildOneBW.png");
	load("MapWildOneTrip", "assets/tiles/MapWildOneTripBW.png");
	load("EarthBender", "assets/tiles/EarthBender4BW.png");
	load("FireLady", "assets/tiles/FireLady4BW.png");
	load("PackMan", "assets/tiles/PackMan4BW.png");
	load("RedFlowers", "assets/tiles/RedFlowersBW.png");
	load("Portal", "assets/tiles/PortalBWY.png");
	load("EvilRabbit", "assets/tiles/EvilRabbit.png");
	load("PinkRabbit", "assets/tiles/PinkRabbit.png");

}

void Assets::SetDynamicMap(string presentMap) { 

	sPresentDynamicMap = presentMap;

	// If it is already loaded
	for (auto dynMap : m_dynamicMaps) {
		if (dynMap.first == presentMap) {
			return;
		}
	}

	// If not, load
	if (presentMap == "DynMap_WildOne") {
		m_dynamicMaps["DynMap_WildOne"] = new cDynamicMap_One;
	}else if (presentMap == "DynMap_WildOneTrip") {
		m_dynamicMaps["DynMap_WildOneTrip"] = new cDynamicMap_OneTrip;
	}

}
