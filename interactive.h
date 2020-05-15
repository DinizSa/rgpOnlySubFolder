#pragma once
#include "dynamic.h"

class Interactive : public Dynamic {
public:
	Interactive();
	Interactive(string name, string asset, float px, float py);
	~Interactive();
	bool OnInteraction(Dynamic* secondDynamic);
};

// <---------------------------- cInteractive_Teleport ---------------------------->
class cInteractive_Teleport: public Interactive {
public:
	cInteractive_Teleport(float posX, float posY, string sTargetDynamicMap, float targetX, float targetY);
	~cInteractive_Teleport();
	bool OnInteraction(Dynamic* secondDynamic) override;

private:
	float targetX, targetY;
	string sTargetDynamicMap;
};

// <---------------------------- cInteractive_Teleport ---------------------------->
class cInteractive_Info: public Interactive {
public:
	cInteractive_Info(string name, float posX, float posY);
	~cInteractive_Info();
	bool OnInteraction(Dynamic* secondDynamic) override;

private:
	float targetX, targetY;
	string sTargetDynamicMap;
};	
