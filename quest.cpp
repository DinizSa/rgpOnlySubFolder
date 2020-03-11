#include "quest.h"
#include "creature.h"

cQuest::cQuest() {
	sName = "";
	bCompleted = false;
}

cQuest::~cQuest() { }



// <------------------------------------ Base quest ------------------------------------>
cQuest_Base::cQuest_Base() { cout << "criada" << endl; }
cQuest_Base::~cQuest_Base(){ cout << "destruida" << endl; }
void cQuest_Base::PopulateDynamics(vector<Dynamic*>& vDynamic, string dynMmapName) {
	if (dynMmapName == "DynMap_WildOne") {
		vDynamic.push_back(new cCreature_PinkRabbit(100, 100));
	}else if (dynMmapName == "DynMap_WildOneTrip") {
		vDynamic.push_back(new cCreature_PinkRabbit(500, 100));
	}
}

void cQuest_Base::OnInteraction(vector<Dynamic*> vDynamic, Dynamic* target) {
	cout << "Interactin gquest" << endl;
}