#pragma once
#include "commands.h"
using namespace std;
#include <list>

class cScriptProcessor {
public:
	cScriptProcessor();

	inline bool getUserControlEnabled() { return this->bUserControlEnabled; }
	void AddCommand(cCommand* cmd);
	void ProcessCommands(int iElapsedTime);

protected:
	bool bUserControlEnabled;
private:
	list<cCommand*> m_listCommands;

};