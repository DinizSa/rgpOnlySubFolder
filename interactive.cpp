#include "interactive.h"
#include "assets.h"

Interactive::Interactive():
	Dynamic() {
}
Interactive::Interactive(string name, float px, float py, float width, float height) :
	Dynamic(name, px, py, 0.f, 0.f, width, height, true, true, true, true, 0) {

}

Interactive::~Interactive() {}

void Interactive::OnInteraction(Dynamic* secondDynamic) {
	cout << this->name << " interacting  with " << secondDynamic->getName() << " (Interactive) " << endl;
}

// <---------------------------- cInteractive_Teleport ---------------------------->

cInteractive_Teleport::cInteractive_Teleport(float posX, float posY, string targetMapName, float targetX, float targetY)
 : Interactive("RedFlowers", posX, posY, 34, 34) {
	this->targetX = targetX;
	this->targetY = targetY;
	this->sTargetMapName = targetMapName;
}

cInteractive_Teleport::~cInteractive_Teleport() {}

void cInteractive_Teleport::OnInteraction(Dynamic* secondDynamic) {
	secondDynamic->setPosX(targetX);
	secondDynamic->setPosY(targetY);
	cout << " Teleporting " << endl;
	// Trigger change on the map
	Assets::get().SetPresentMap("MapWildOneTrip");
}