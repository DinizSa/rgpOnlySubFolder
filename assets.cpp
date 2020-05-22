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
	load("MapLevelOne", "assets/tiles/MapLevelOne.png");
	load("MapArenaOne", "assets/tiles/MapLevelOne.png");
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
	load("scroll", "assets/tiles/scroll.png");
	load("Sword", "assets/tiles/sword.png");
	load("Sword4", "assets/tiles/sword4.png");
	load("fireball", "assets/tiles/fireball4.png");
	load("sock", "assets/tiles/sock.png");
	load("amate", "assets/tiles/amate.jpg");
	load("magicStaff", "assets/tiles/magicStaff.png");
	load("Rings", "assets/tiles/rings.jpg");
	load("rock", "assets/tiles/rock.png");
	load("transparent", "assets/tiles/transparent.png");

	// Backgrounds
	load("bgpCloudsIsland", "assets/tiles/bgpCloudsIsland.jpg");
	load("bgpCityFog", "assets/tiles/bgpCityFog.png");
	load("bgpSunset", "assets/tiles/bgpSunset.png");
	// Filter maps
	load("mapCold", "assets/tiles/mapCold.png");
	//load("mapMinado", "assets/tiles/mapInvert.jpg");
	load("mapIllusion", "assets/tiles/mapIllusion.jpg");
	load("mapDreaming", "assets/tiles/mapDreaming.jpg");
	load("mapSmoke", "assets/tiles/mapSmoke.jpg");
	load("mapPen", "assets/tiles/mapPen.png");
	load("mapPolygons", "assets/tiles/mapPolygons.png");
}
