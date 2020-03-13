#include "quest.h"
#include "creature.h"
#include "assets.h"
vector<cQuest*> cQuest::vQuest;
cQuest::cQuest() {
	sName = "";
	bCompleted = false;
}

cQuest::~cQuest() { }



// <------------------------------------ Base quest ------------------------------------>
cQuest_Base::cQuest_Base() {  }
cQuest_Base::~cQuest_Base(){ }
void cQuest_Base::PopulateDynamics(vector<Dynamic*>& vDynamic, string dynMmapName) {
	if (dynMmapName == "DynMap_WildOne") {
		vDynamic.push_back(new cCreature_PinkRabbit(100, 100));
	}else if (dynMmapName == "DynMap_WildOneTrip") {
		vDynamic.push_back(new cCreature_PinkRabbit(500, 100));
	} 
}

bool cQuest_Base::OnInteraction(vector<Dynamic*> vDynamic, Dynamic* target) {
	cout << "INSIDE QUEST. cQuest_Base OnInteraction: ";

	if (target->getName() == "FireLady" && Assets::get().GetNameDynamicMap() == "DynMap_WildOne") {
		cout << " FireLady & DynMap_WildOne" << endl;
		return true;
	}
	if (target->getName() == "FireLady" && Assets::get().GetNameDynamicMap() == "DynMap_WildOneTrip") {
		cout << "FireLady & DynMap_WildOneTrip" << endl;
		return true;
	}
	if (target->getName() == "EarthBender") {
		cout << "EarthBender & DynMap_WildOneTrip" << endl;
		return true;
	}
	cout << "FALSE !!!!!" << endl;
	return false;
}