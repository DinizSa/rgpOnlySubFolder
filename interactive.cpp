#include "interactive.h"
#include "assets.h"

Interactive::Interactive():
	Dynamic() {
}
Interactive::Interactive(string name, float px, float py) :
	Dynamic(name, px, py, true, true, true, true, 0) {

}

Interactive::~Interactive() {}

void Interactive::OnInteraction(Dynamic* secondDynamic) {
	cout << this->name << " interacting  with " << secondDynamic->getName() << " (Interactive) " << endl;
}

// <---------------------------- cInteractive_Teleport ---------------------------->

cInteractive_Teleport::cInteractive_Teleport(float posX, float posY, string sTargetDynamicMap, float targetX, float targetY)
 : Interactive("RedFlowers", posX, posY) {
	this->sTargetDynamicMap = sTargetDynamicMap;
	this->targetX = targetX;
	this->targetY = targetY;
}

cInteractive_Teleport::~cInteractive_Teleport() {}

void cInteractive_Teleport::OnInteraction(Dynamic* secondDynamic) {
	Assets::get().SetNameDynamicMap(sTargetDynamicMap);
	secondDynamic->setPosX(targetX);
	secondDynamic->setPosY(targetY);
}