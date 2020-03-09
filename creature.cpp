#include "creature.h"
#include "scriptProcessor.h"

Creature::Creature(): Dynamic() {
	hp = 0;
	maxHp = 0;
}
Creature::~Creature() {
}
Creature::Creature(string name, float px, float py, bool solidVsSolid, bool solidVsDynamic, bool friendly, int maxHp, float maxSpeed):
	Dynamic(name, px, py, solidVsSolid, solidVsDynamic, friendly, true, maxSpeed){
	this->hp = maxHp;
	this->maxHp = maxHp;
}

void Creature::OnInteraction(Dynamic* secondDynamic) {
	cout << this->name << " interacting with " << secondDynamic->getName() << endl;
}


// <------------------------------------ Fire Lady --------------------------------------------->
cCreature_FireLady::cCreature_FireLady(): Creature("FireLady", 550, 500, 1, 1, 1, 50, 1.5f) {};

void cCreature_FireLady::OnInteraction(Dynamic* secondDynamic) {
	cScriptProcessor::Get().AddCommand(new cCommand_Talk("Hi I am Fire Lady! ", 1500, sf::Color::Red));
}

// <------------------------------------ Earth Bender --------------------------------------------->
cCreature_EarthBender::cCreature_EarthBender() : Creature("EarthBender", 550, 400, 1, 1, 1, 50, 1.5f) {};

void cCreature_EarthBender::OnInteraction(Dynamic* secondDynamic) {
	cScriptProcessor::Get().AddCommand(new cCommand_MoveTo(this, secondDynamic->getPosX() + 100, this->py));
	cScriptProcessor::Get().AddCommand(new cCommand_MoveTo(this, secondDynamic->getPosX() + 100, secondDynamic->getPosY()));
	cScriptProcessor::Get().AddCommand(new cCommand_MoveTo(this, secondDynamic->getPosX() + 20, secondDynamic->getPosY()));
	cScriptProcessor::Get().AddCommand(new cCommand_Talk("Hi I am Earth bender! ", 1500, sf::Color::Color({ 200, 100, 0, 255 })));
}


// <------------------------------------ Evil Rabbit --------------------------------------------->
cCreature_EvilRabbit::cCreature_EvilRabbit() : Creature("EvilRabbit", 400, 400, 1, 1, 1, 50, 1.5f) {};

void cCreature_EvilRabbit::OnInteraction(Dynamic* secondDynamic) {
	cScriptProcessor::Get().AddCommand(new cCommand_Talk("Cri Cri! The rabbit day will come!", 1000, sf::Color::Red));
	cScriptProcessor::Get().AddCommand(new cCommand_MoveTo(this, this->getPosX() + 300, this->getPosY()));
}

void cCreature_EvilRabbit::updateAI(Dynamic* pPlayer) {
	cout << "Rabbit AI is being cvalled" << endl;
	this->addVelocityNormalizedXY(1, -0.5);

}
