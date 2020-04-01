#include "quest.h"
#include "creature.h"
#include "assets.h"
#include "scriptProcessor.h"
#include "item.h"

vector<shared_ptr<cQuest>> cQuest::vQuest;

cQuest::cQuest(string sName) {
	this->sName = sName;
}

cQuest::~cQuest() {}


void cQuest::addQuest(shared_ptr<cQuest> questToAdd) { 
	// Check if is already in vQuest
	for (unsigned i = 0; i < cQuest::vQuest.size(); i++)
		if (cQuest::vQuest[i]->getName() == questToAdd->getName())
			return;
	cQuest::vQuest.push_back(questToAdd); 
};

void cQuest::removeQuest(string questName) {
	for (int i = 0; i < cQuest::vQuest.size(); i++) {
		if (cQuest::vQuest[i]->getName() == questName) {
			cQuest::vQuest.erase(cQuest::vQuest.begin()+i);
			return;
		}
	}
}

// <------------------------------------ Base quest ------------------------------------>
cQuest_Base::cQuest_Base():cQuest("Base quest") {  }
cQuest_Base::~cQuest_Base() { }
void cQuest_Base::PopulateDynamics(vector<Dynamic*>& vDynamic, string dynMmapName) {
	if (dynMmapName == "DynMap_WildOne") {
		vDynamic.push_back(new cCreature_PinkRabbit("Pink Rabbit",3, 3));
	}else if (dynMmapName == "DynMap_WildOneTrip") {
		vDynamic.push_back(new cCreature_PinkRabbit("Pink Rabbit",15, 3));
	} 
}

bool cQuest_Base::OnInteraction(vector<Dynamic*> vDynamic, Dynamic* target) {
	cQuest::getQuestVector()->size();
	if (target->getName() == "Joseph" ) {
		if (cQuest::getQuestVector()->size() < 2) {
			cScriptProcessor::Get().AddCommand(new cCommand_Talk("You must find quests!", 1500));
			return true;
		}
		else {
			cScriptProcessor::Get().AddCommand(new cCommand_Talk("Good luck on your journey!", 1500));
			return true;
		}
	}
	if (target->getName() == "Joseph brother") {
		cScriptProcessor::Get().AddCommand(new cCommand_Talk("Ask my brother Joseph about your quests!", 1500));
		return true;
	}
	return false;
}

// <------------------------------------ Find Pink Rabbit quest ------------------------------------>
cQuest_FindThePinkRabbit::cQuest_FindThePinkRabbit() :cQuest("Find pink Rabbit") { 
	rabbitFound = false;
	cScriptProcessor::Get().AddCommand(new cCommand_Talk("Please help me find Mr Evil rabbit!", 1500));
}
cQuest_FindThePinkRabbit::~cQuest_FindThePinkRabbit() { }
void cQuest_FindThePinkRabbit::PopulateDynamics(vector<Dynamic*>& vDynamic, string dynMmapName) {
	if (dynMmapName == "DynMap_WildOneTrip") {
		vDynamic.push_back(new cCreature_PinkRabbit("Pink Rabbit",19, 15));
	} 
}

bool cQuest_FindThePinkRabbit::OnInteraction(vector<Dynamic*> vDynamic, Dynamic* target) {

	if (target->getName() == "Matilda" ) {
		if (!rabbitFound) {
			cScriptProcessor::Get().AddCommand(new cCommand_Talk("You must find the Pink Acid Rabbit !", 1500));
			return true;
		}
		else {
			cScriptProcessor::Get().AddCommand(new cCommand_Talk("Thank you so much sir!", 1500));
			cScriptProcessor::Get().AddCommand(new cCommand_Talk("Take this scroll and may it guide you!", 1500));
			vDynamic[0]->addItem(new cItem_ScrollBandidosTruth());
			cQuest::removeQuest(this->getName());
			return true;
		}
	}
	else if (target->getAssetName() == "PinkRabbit" /*&& Assets::get().GetNameDynamicMap() == "DynMap_WildOneTrip"*/) {
		if (!rabbitFound) {
			this->rabbitFound = true;
			cScriptProcessor::Get().AddCommand(new cCommand_Talk("DAMM you found me !", 1500));
			return true;
		}
		else {
			this->rabbitFound = true;
			cScriptProcessor::Get().AddCommand(new cCommand_Talk("Ok you won, now fk off !", 1500));
			return true;
		}
	}
	return false;
}
