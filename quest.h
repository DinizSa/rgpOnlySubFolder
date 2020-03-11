#pragma once
#include "dynamic.h"

class cQuest {
public:
	cQuest();
	~cQuest();
	inline bool isCompleted() { return bCompleted; };
	inline string getName() { return sName; };
	// Current dynamics and map
	virtual void PopulateDynamics(vector<Dynamic*>& vDynamic, string mapName) = 0;
	// Current dynamics and the target interacted, so we can specify each case
	virtual bool OnInteraction(vector<Dynamic*> vDynamic, Dynamic* target) = 0;

protected:
	string sName;
	bool bCompleted;
};

// <------------------------------------ Base quest ------------------------------------>
class cQuest_Base : public cQuest {
public:
	cQuest_Base();
	~cQuest_Base();
	void PopulateDynamics(vector<Dynamic*>& vDynamic, string mapName) override;
	bool OnInteraction(vector<Dynamic*> vDynamic, Dynamic* target) override;

};