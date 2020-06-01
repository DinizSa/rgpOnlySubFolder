#pragma once
#include "dynamic.h"

class cQuest {
public:
	cQuest(string sName);
	~cQuest();
	inline string getName() { return sName; };
	// Current dynamics and map
	virtual void PopulateDynamics(vector<Dynamic*>& vDynamic, string mapName) = 0;
	// Current dynamics and the target interacted, so we can specify each case
	virtual bool OnInteraction(vector<Dynamic*> vDynamic, Dynamic* target) = 0;

	// Quest manager interface
	static inline vector<shared_ptr<cQuest>>* getQuestVector() { return &cQuest::vQuest; };
	static void addQuest(shared_ptr<cQuest> questToAdd);
	static void removeQuest(string questToRemove);
	static inline bool hasNewQuest() { return cQuest::newQuest; };
	static inline void setNewQuest(bool _newQuest) { cQuest::newQuest = _newQuest; };

private:
	static bool newQuest;

protected:
	string sName;
	static vector<shared_ptr<cQuest>> vQuest;
	bool bCompleted;
	bool bAdded;
};

// <------------------------------------ Base quest ------------------------------------>
class cQuest_Base : public cQuest {
public:
	cQuest_Base();
	~cQuest_Base();
	void PopulateDynamics(vector<Dynamic*>& vDynamic, string mapName) override;
	bool OnInteraction(vector<Dynamic*> vDynamic, Dynamic* target) override;
	
};

// <------------------------------------ Earth bending quest ------------------------------------->
class cQuest_LearnEarthBending : public cQuest {
public:
	cQuest_LearnEarthBending();
	~cQuest_LearnEarthBending();
	void PopulateDynamics(vector<Dynamic*>& vDynamic, string mapName) override;
	bool OnInteraction(vector<Dynamic*> vDynamic, Dynamic* target) override;


};