#include "quest.h"
#include "creature.h"
#include "assets.h"

cQuest::cQuest() {
	sName = "";
	bCompleted = false;
}

cQuest::~cQuest() { }



// <------------------------------------ Base quest ------------------------------------>
cQuest_Base::cQuest_Base() { }
cQuest_Base::~cQuest_Base(){ }
void cQuest_Base::PopulateDynamics(vector<Dynamic*>& vDynamic, string dynMmapName) {
	if (dynMmapName == "DynMap_WildOne") {
		vDynamic.push_back(new cCreature_PinkRabbit(100, 100));
	}else if (dynMmapName == "DynMap_WildOneTrip") {
		vDynamic.push_back(new cCreature_PinkRabbit(500, 100));
	} 
}

bool cQuest_Base::OnInteraction(vector<Dynamic*> vDynamic, Dynamic* target) {
	cout << "QUEST OnInteraction" << endl;

	if (target->getName() == "FireLady" && Assets::get().GetNameDynamicMap() == "DynMap_WildOneTrip") {
		cout << "QUEST FireLady on DynMap_WildOne" << endl;
		return true;
	}
	return false;
}