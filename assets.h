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
	inline int GetSizeSprite(string name) { return mapSizeSprite[name]; }

	//inline string GetNameMap() { return sPresentMap; }
	//inline void SetNameMap(string presentMap) { sPresentMap = presentMap; }
	//inline Maps* GetCurrentMap() { return m_maps[sPresentMap]; }

	inline string GetNameDynamicMap() { return sPresentDynamicMap; }
	inline void SetNameDynamicMap(string presentMap) { sPresentDynamicMap = presentMap; }
	inline cDynamicMap* GetCurrentDynamicMap() { return m_dynamicMaps[sPresentDynamicMap]; }

	void LoadTextures();
	//void LoadMaps();
	void LoadDynamicMaps();


private:
	//string sPresentMap;
	string sPresentDynamicMap;
	// Turn constructor and destructor invisible to the outside
	Assets();
	~Assets();
	map<string, sf::Texture> m_mapsTextures;
	//map<string, Maps*> m_maps;
	map<string, cDynamicMap*> m_dynamicMaps;
	map<string, int> mapSizeSprite;
};