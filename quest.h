#pragma once
#include "dynamic.h"

class cQuest {
public:
	cQuest();
	~cQuest();
	inline bool isCompleted() { return bCompleted; };
	inline string getName() { return sName; };
	// Current dynamics and map
	virtual void PopulateDynamics(vector<Dynamic*> vDynamic, string mapName);
	// Current dynamics and the target interacted, so we can specify each case
	virtual void OnInteraction(vector<Dynamic*> vDynamic, Dynamic* target);

protected:
	string sName;
	bool bCompleted;


};