#include "scriptProcessor.h"

cScriptProcessor::cScriptProcessor() {
	bUserControlEnabled = true;
}
cScriptProcessor::~cScriptProcessor() {
	for (auto command : m_listCommands)
		delete command;
}

void cScriptProcessor::AddCommand(cCommand* cmd) {
	this->m_listCommands.push_back(cmd);
}

void cScriptProcessor::ProcessCommands(int iElapsedTime) {
	bUserControlEnabled = m_listCommands.empty();

	// If has commands in the queue
	if (!m_listCommands.empty()) {

		// Front command is not completed
		if (!m_listCommands.front()->getCompleted()) {
			if (!m_listCommands.front()->getStarted()) {
				m_listCommands.front()->setStarted();

			}
			else {
				m_listCommands.front()->Update();
			}
		}
		else {
			m_listCommands.pop_front();
		}
	}
}