#include "interactive.h"
#include "assets.h"
#include "constants.h"
#include "scriptProcessor.h"

Interactive::Interactive():
	Dynamic() {
}
Interactive::Interactive(string name, string asset, float px, float py, bool solidVsSolid, bool solidVsDynamic) :
	Dynamic(name, asset, px, py, solidVsSolid, solidVsDynamic, true, true, 0, false) {
	// For simplicity, interactives name will be their assets name
}

Interactive::~Interactive() {}

bool Interactive::OnInteraction(Dynamic* secondDynamic) {
	cout << this->getName() << " interacting  with " << secondDynamic->getName() << " (Interactive) " << endl;
	return false;
}

// <---------------------------- cInteractive_Teleport ---------------------------->

cInteractive_Teleport::cInteractive_Teleport(float posX, float posY, string sTargetDynamicMap, float targetX , float targetY)
 : Interactive("Teleport", "transparent", posX, posY, false, false) {
	this->sTargetDynamicMap = sTargetDynamicMap;
	this->targetX = targetX * constants::ASSET_SIZE;
	this->targetY = targetY * constants::ASSET_SIZE;
}

cInteractive_Teleport::~cInteractive_Teleport() {}

bool cInteractive_Teleport::OnInteraction(Dynamic* secondDynamic) {
	Assets::get().SetNameDynamicMap(sTargetDynamicMap);
	secondDynamic->setPosX(targetX);
	secondDynamic->setPosY(targetY);
	return false;
}



// <---------------------------- cInteractive_Teleport ---------------------------->

cInteractive_Info::cInteractive_Info(string name, float posX, float posY)
 : Interactive(name, "rock", posX, posY, true, true) {
	this->sTargetDynamicMap = sTargetDynamicMap;
	this->targetX = targetX * constants::ASSET_SIZE;
	this->targetY = targetY * constants::ASSET_SIZE;
}

cInteractive_Info::~cInteractive_Info() {}

bool cInteractive_Info::OnInteraction(Dynamic* secondDynamic) {

	cScriptProcessor::Get().AddCommand(new cCommand_Talk(this->getName(), "Use the keys W, A, S, D to move", 1500));
	cScriptProcessor::Get().AddCommand(new cCommand_Talk(this->getName(), "SPACE to interact", 1500));
	cScriptProcessor::Get().AddCommand(new cCommand_Talk(this->getName(), "M to acess the inventory", 1500));
	cScriptProcessor::Get().AddCommand(new cCommand_Talk(this->getName(), "and E do attack", 1500));
	cScriptProcessor::Get().AddCommand(new cCommand_Talk(this->getName(), "Good luck", 1500));
	return false;
}

