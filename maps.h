#pragma once
#include "landscape.h"
//#include "interactive.h"

class Maps {
public:
	Maps(string sName);
	~Maps();
	void draw(sf::RenderWindow* window);
	bool getSolid(int x, int y);
	inline int getNrHorizontal() { return nrHorizontal; }
	inline int getNrVertical() { return nrVertical; }
	inline string getName() { return sName; }

private:
	Landscape* landscapes;
	int* indicesMap;
	bool* solidMap;
	int nrHorizontal, nrVertical;
	string sName;

};

//class Maps_WildOne : public Maps {
//public:
//	Maps_WildOne();
//};
//
//class Maps_WildOneTrip : public Maps {
//public:
//	Maps_WildOneTrip();
//};