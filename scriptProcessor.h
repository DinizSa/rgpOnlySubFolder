#pragma once
#include "command.h"
using namespace std;
#include <list>

class cScriptProcessor {
public:

	static cScriptProcessor& Get() {
		static cScriptProcessor me;
		// Init
		//me.bUserControlEnabled = true;
		return me;
	}
	cScriptProcessor(cScriptProcessor const&) = delete;
	void operator = (cScriptProcessor const&) = delete;

	inline bool getUserControlEnabled() { return this->bUserControlEnabled; }
	void AddCommand(cCommand* cmd);
	void ProcessCommands(int iElapsedTime);

protected:
	bool bUserControlEnabled;
private:
	list<cCommand*> m_listCommands;
	cScriptProcessor();
};