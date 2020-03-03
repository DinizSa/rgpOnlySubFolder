#pragma once
#include "dynamic.h"

class Interactive : public Dynamic {
public:
	Interactive();
	Interactive(string name, float px, float py, float width, float height);
	~Interactive();
	void OnInteraction(Dynamic* secondDynamic);
};

// <---------------------------- cInteractive_Teleport ---------------------------->
class cInteractive_Teleport: public Interactive {
public:
	cInteractive_Teleport(float posX, float posY, string targetMapName, float targetX, float targetY);
	~cInteractive_Teleport();
	void OnInteraction(Dynamic* secondDynamic) override;

private:
	float targetX, targetY;
	string sTargetMapName;
};