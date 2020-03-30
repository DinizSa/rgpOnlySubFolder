#include "interactive.h"
#include "assets.h"

Interactive::Interactive():
	Dynamic() {
}
Interactive::Interactive(string asset, float px, float py) :
	Dynamic(asset, asset, px, py, true, true, true, true, 0, false) {
	// For simplicity, interactives name will be their assets name
}

Interactive::~Interactive() {}

bool Interactive::OnInteraction(Dynamic* secondDynamic) {
	cout << this->getName() << " interacting  with " << secondDynamic->getName() << " (Interactive) " << endl;
	return false;
}

// <---------------------------- cInteractive_Teleport ---------------------------->

cInteractive_Teleport::cInteractive_Teleport(float posX, float posY, string sTargetDynamicMap, float targetX, float targetY)
 : Interactive("RedFlowers", posX, posY) {
	this->sTargetDynamicMap = sTargetDynamicMap;
	this->targetX = targetX;
	this->targetY = targetY;
}

cInteractive_Teleport::~cInteractive_Teleport() {}

bool cInteractive_Teleport::OnInteraction(Dynamic* secondDynamic) {
	Assets::get().SetNameDynamicMap(sTargetDynamicMap);
	secondDynamic->setPosX(targetX);
	secondDynamic->setPosY(targetY);
	return false;
}