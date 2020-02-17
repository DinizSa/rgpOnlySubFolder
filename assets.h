#pragma once
#include <SFML/Graphics.hpp>
#include <map>
using namespace std;

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
	int GetSizeSprite(string name) {
		return mapSizeSprite[name];
	}

	void LoadTextures();


private:
	// Turn constructor and destructor invisible to the outside
	Assets();
	~Assets();
	map<string, sf::Texture> m_mapsTextures;
	map<string, int> mapSizeSprite;
};