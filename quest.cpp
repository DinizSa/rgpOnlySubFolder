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
			cScriptProcessor::Get().AddCommand(new cCommand_Talk(target->getName(), "You must find quests!", 1500));
			return true;
		}
		else {
			cScriptProcessor::Get().AddCommand(new cCommand_Talk(target->getName(), "Good luck on your journey!", 1500));
			return true;
		}
	}
	if (target->getName() == "Joseph brother") {
		cScriptProcessor::Get().AddCommand(new cCommand_Talk(target->getName(), "Ask my brother Joseph about your quests!", 1500));
		return true;
	}
	return false;
}

// <------------------------------------ Find Gustavo sock - quest ------------------------------------>
cQuest_FindThePinkRabbit::cQuest_FindThePinkRabbit() :cQuest("Find pink Rabbit") { 
	rabbitFound = false;
}
cQuest_FindThePinkRabbit::~cQuest_FindThePinkRabbit() { }
void cQuest_FindThePinkRabbit::PopulateDynamics(vector<Dynamic*>& vDynamic, string dynMmapName) {
	if (dynMmapName == "DynMap_WildOneTrip") {
		vDynamic.push_back(new cCreature_PinkRabbit("Pink Rabbit",2, 10));
		vDynamic.push_back(new cCreature_EvilRabbit("Evil Rabbit", 3, 9));
		vDynamic.push_back(new cCreature_EvilRabbit("Evil Rabbit", 3, 11));
	} 
}

bool cQuest_FindThePinkRabbit::OnInteraction(vector<Dynamic*> vDynamic, Dynamic* target) {

	if (target->getName() == "Gustavo Santos" ) {
		if (!rabbitFound) {
			cScriptProcessor::Get().AddCommand(new cCommand_Talk(target->getName(), "A mente chama-se mente...", 2000));
			cScriptProcessor::Get().AddCommand(new cCommand_Talk(vDynamic[0]->getName(),"Não acabas a frase?", 1500));
			cScriptProcessor::Get().AddCommand(new cCommand_Talk(target->getName(), "Um coelho roubou-me a meia", 2000));
			cScriptProcessor::Get().AddCommand(new cCommand_Talk(target->getName(), "das drogas.", 1500));
			cScriptProcessor::Get().AddCommand(new cCommand_Talk(target->getName(), "Preciso delas para me inspirar", 2000));
			return true;
		}
		else {
			cScriptProcessor::Get().AddCommand(new cCommand_Talk(vDynamic[0]->getName(), "Encontrei a meia Gustavo", 1500));
			cScriptProcessor::Get().AddCommand(new cCommand_Talk(target->getName(), "Toma este livro como recompensa.", 1500));
			vDynamic[0]->addItem(new cItem_Scroll);
			vDynamic[0]->consumeItem("Meia", 0);
			cQuest::removeQuest(this->getName());
			return true;
		}
	}
	else if (target->getName() == "Pink Rabbit" && Assets::get().GetNameDynamicMap() == "DynMap_WildOneTrip") {
		if (!rabbitFound) {
			this->rabbitFound = true;
			cScriptProcessor::Get().AddCommand(new cCommand_Talk(target->getName(), "Tou todo fodido", 1500));
			cScriptProcessor::Get().AddCommand(new cCommand_Talk(target->getName(), "Leva a meia", 1500));
			vDynamic[0]->addItem(new cItem_Calcetine);
			return true;
		}
		else {
			this->rabbitFound = true;
			cScriptProcessor::Get().AddCommand( new cCommand_Talk(target->getName(), "Saudades da meia", 1500));
			return true;
		}
	}
	return false;
}
