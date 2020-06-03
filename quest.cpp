#include "quest.h"
#include "creature.h"
#include "assets.h"
#include "scriptProcessor.h"
#include "item.h"

vector<shared_ptr<cQuest>> cQuest::vQuest;

bool cQuest::newQuest = false;

cQuest::cQuest(string sName) {
	this->sName = sName;
	this->bAdded = false;
	this->bCompleted = false;
}

cQuest::~cQuest() {}


void cQuest::addQuest(shared_ptr<cQuest> questToAdd) { 
	cQuest::setNewQuest(true);
	// Check if is already in vQuest
	for (unsigned i = 0; i < cQuest::vQuest.size(); i++)
		if (cQuest::vQuest[i]->getName() == questToAdd->getName())
			return;
	cout << "quest added: " << questToAdd->getName() << endl;
	cQuest::vQuest.push_back(questToAdd);
};

void cQuest::removeQuest(string questName) {
	cout << "quest removed: " << questName << endl;
	for (int i = 0; i < cQuest::vQuest.size(); i++) {
		if (cQuest::vQuest[i]->getName() == questName) {
			cQuest::vQuest.erase(cQuest::vQuest.begin()+i);
			return;
		}
	}
}

// <------------------------------------ Earth bending quest ------------------------------------->

cQuest_LearnEarthBending::cQuest_LearnEarthBending():cQuest("Learn Earth Bending") {
};
cQuest_LearnEarthBending::~cQuest_LearnEarthBending() {};
void cQuest_LearnEarthBending::PopulateDynamics(vector<Dynamic*>& vDynamic, string mapName) {
	
	vDynamic.push_back(new cCreature_EvilRabbit("Evil Rabbit", 2, 5));
};
bool cQuest_LearnEarthBending::OnInteraction(vector<Dynamic*> vDynamic, Dynamic* target) {
	if (target->getName() == "Earth Bender" && !this->bAdded) {
		cScriptProcessor::Get().AddCommand(new cCommand_Talk(this->getName(), "Take my sword", 100));
		cScriptProcessor::Get().AddCommand(new cCommand_Talk(this->getName(), "and banish evil", 100));
		vDynamic[0]->addItem(new cItem_Sword(10, 0, 0));
		this->bAdded = true;
		return true;
	}else if (target->getName() == "Earth Bender" && this->bAdded && !this->bCompleted) {
		cScriptProcessor::Get().AddCommand(new cCommand_Talk(target->getName(), "Good luck", 100));
		return true;
	}
	return false;
};


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
			cScriptProcessor::Get().AddCommand(new cCommand_Talk(target->getName(), "You must find quests!", 100));
			return true;
		}
		else {
			cScriptProcessor::Get().AddCommand(new cCommand_Talk(target->getName(), "Good luck on your journey!", 100));
			return true;
		}
	}
	if (target->getName() == "Joseph brother") {
		cScriptProcessor::Get().AddCommand(new cCommand_Talk(target->getName(), "Ask my brother Joseph about your quests!", 100));
		return true;
	}
	return false;
}

