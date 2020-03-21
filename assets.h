#pragma once
using namespace std;
#include <SFML/Graphics.hpp>
#include <map>
#include "maps.h"
#include "dynamicMap.h"

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

	inline sf::Texture& GetTexture(string name) { return m_mapsTextures[name]; }
	inline int GetSizeSprite() { return iSizeSprite; }

	inline string GetNameDynamicMap() { return sPresentDynamicMap; }
	void SetNameDynamicMap(string presentMap) { sPresentDynamicMap = presentMap; };

	void LoadTextures();


private:
	// Turn constructor and destructor invisible to the outside as a singleton
	Assets();
	~Assets();

	string sPresentDynamicMap;
	map<string, sf::Texture> m_mapsTextures;
	map<string, cDynamicMap*> m_dynamicMaps;
	int iSizeSprite;
};