#include "scriptProcessor.h"

cScriptProcessor::cScriptProcessor() {

}

void cScriptProcessor::AddCommand(cCommand* cmd) {
	this->m_listCommands.push_back(cmd);
}

void cScriptProcessor::ProcessCommands(int iElapsedTime) {
	bUserControlEnabled = m_listCommands.empty();

	// If has commands in the queue
	if (!m_listCommands.empty()) {

		// Front command is not completed
		if (!m_listCommands.front()->isCompleted()) {
			if (!m_listCommands.front()->getStarted()) {
				m_listCommands.front()->setStarted();
				m_listCommands.front()->Start();
				cout << "started" << endl;

			}
			else {
				m_listCommands.front()->Update(iElapsedTime);
			}
		}
		else {
			//delete m_listCommands.front();
			cout << "stopped" << endl;
			m_listCommands.pop_front();
		}
	}
}