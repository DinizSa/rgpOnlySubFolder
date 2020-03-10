#include "creature.h"
#include "scriptProcessor.h"
#include "assets.h"

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
cCreature_FireLady::cCreature_FireLady(float px, float py): Creature("FireLady", px, py, 1, 1, 1, 50, 1.5f) {};

void cCreature_FireLady::OnInteraction(Dynamic* secondDynamic) {
	cScriptProcessor::Get().AddCommand(new cCommand_Talk("Hi I am Fire Lady! ", 1500, sf::Color::Red));
}

// <------------------------------------ Earth Bender --------------------------------------------->
cCreature_EarthBender::cCreature_EarthBender(float px, float py) : Creature("EarthBender", px, py, 1, 1, 1, 50, 1.5f) {};

void cCreature_EarthBender::OnInteraction(Dynamic* secondDynamic) {
	cScriptProcessor::Get().AddCommand(new cCommand_MoveTo(this, secondDynamic->getPosX() + 100, this->py));
	cScriptProcessor::Get().AddCommand(new cCommand_MoveTo(this, secondDynamic->getPosX() + 100, secondDynamic->getPosY()));
	cScriptProcessor::Get().AddCommand(new cCommand_MoveTo(this, secondDynamic->getPosX(), secondDynamic->getPosY()));
	cScriptProcessor::Get().AddCommand(new cCommand_Talk("Hi I am Earth bender! ", 1500, sf::Color::Color({ 200, 100, 0, 255 })));
}


// <------------------------------------ Evil Rabbit --------------------------------------------->
cCreature_EvilRabbit::cCreature_EvilRabbit(float px, float py) : Creature("EvilRabbit", px, py, 1, 1, 1, 50, 1.0f) {};

void cCreature_EvilRabbit::OnInteraction(Dynamic* secondDynamic) {
	cScriptProcessor::Get().AddCommand(new cCommand_Talk("Cri Cri!", 1000, sf::Color::Red));
}

void cCreature_EvilRabbit::updateAI(Dynamic* pPlayer) {
	float dx = this->px - pPlayer->getPosX();
	float dy = this->py - pPlayer->getPosY();
	float delta = sqrtf(dx * dx + dy * dy);
	if (framesOfRest == 0)
		framesOfRest = 60 * 4;

	if(framesOfRest > 60*3 && abs(delta) > Assets::get().GetSizeSprite("RespectableDistance"))
		this->addVelocityNormalizedXY(-dx / delta, -dy / delta);

	framesOfRest--;
}

// <------------------------------------ Pink Friendly Rabbit --------------------------------------------->
cCreature_PinkRabbit::cCreature_PinkRabbit(float px, float py) : Creature("PinkRabbit", px, py, 1, 1, 1, 50, 1.0f) {};

void cCreature_PinkRabbit::OnInteraction(Dynamic* secondDynamic) {
	cScriptProcessor::Get().AddCommand(new cCommand_Talk("Cri Cri!", 1000, sf::Color::Red));
}

void cCreature_PinkRabbit::updateAI(Dynamic* pPlayer) {
	float dx = this->px - pPlayer->getPosX();
	float dy = this->py - pPlayer->getPosY();
	float delta = sqrtf(dx * dx + dy * dy);

	if (framesOfRest == 0)
		framesOfRest = 60 * 2;

	if (framesOfRest > 60  && abs(delta) < 100)
		this->addVelocityNormalizedXY(dx / delta, dy / delta);

	framesOfRest--;
}
