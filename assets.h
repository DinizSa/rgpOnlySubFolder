#pragma once
#include <SFML/Graphics.hpp>
#include <map>
using namespace std;
#include "maps.h"

class Assets {

public:
	// SINGLETON -> so assets are not load again
	// Return the reference to the instance to itself
	static Assets& get() {
		static Assets me;
		return me;
	}
	// Delete copy methods
	Assets(Assets const&) = delete; // Get rid of the default copy constructor
	void operator = (Assets const&) = delete; // assign to other variable would make a small copy of this object

	sf::Texture& GetTexture(string name) {
		return m_mapsTextures[name];
	}
	Maps* GetMaps(string name) {
		return m_mapsMaps[name];
	}
	int GetSizeSprite(string name) {
		return mapSizeSprite[name];
	}

	string GetPresentMap() { return sPresentMap; }
	void SetPresentMap(string presentMap) { sPresentMap = presentMap; }

	void LoadTextures();
	void LoadMaps();


private:
	string sPresentMap;
	// Turn constructor and destructor invisible to the outside
	Assets();
	~Assets();
	map<string, sf::Texture> m_mapsTextures;
	map<string, Maps*> m_mapsMaps;
	map<string, int> mapSizeSprite;
};