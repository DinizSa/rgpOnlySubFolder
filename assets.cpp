#include "assets.h"

Assets::Assets() {
	iSizeSprite = 34;
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
	// Color
	load("MapWildOne", "assets/tiles/MapWildOne.png");
	load("MapWildOneTrip", "assets/tiles/MapWildOneTrip.png");
	load("EarthBender", "assets/tiles/EarthBender4.png");
	load("FireLady", "assets/tiles/FireLady4.png");
	load("PackMan", "assets/tiles/PackMan4.png");
	load("RedFlowers", "assets/tiles/RedFlowers.png");
	load("Portal", "assets/tiles/PortalBWY.png");
	load("EvilRabbit", "assets/tiles/EvilRabbit.png");
	load("PinkRabbit", "assets/tiles/PinkRabbit.png");
	load("hearth", "assets/tiles/hearth.png");
	load("shroom", "assets/tiles/shroom.png");
	   
	//// B&W
	//load("MapWildOne", "assets/tiles/MapWildOneBW.png");
	//load("MapWildOneTrip", "assets/tiles/MapWildOneTripBW.png");
	//load("EarthBender", "assets/tiles/EarthBender4BW.png");
	//load("FireLady", "assets/tiles/FireLady4BW.png");
	//load("PackMan", "assets/tiles/PackMan4BW.png");
	//load("RedFlowers", "assets/tiles/RedFlowersBW.png");
	//load("Portal", "assets/tiles/PortalBWY.png");
	//load("EvilRabbit", "assets/tiles/EvilRabbit.png");
	//load("PinkRabbit", "assets/tiles/PinkRabbit.png");
	//load("hearth", "assets/tiles/hearth.png");
	//load("shroom", "assets/tiles/shroom.png");

}
