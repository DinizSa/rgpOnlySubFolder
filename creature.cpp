#include "creature.h"
#include "scriptProcessor.h"
#include "assets.h"
#include "quest.h"
#include "textDrawer.h"
#include "item.h"

Creature::Creature(): Dynamic() {
	hp = 0;
	maxHp = 0;

}
//Creature::~Creature() {
//}
Creature::Creature(string name, string asset, float px, float py, bool solidVsSolid, bool solidVsDynamic, bool friendly, int maxHp, float maxSpeed):
	Dynamic(name, asset, px, py, solidVsSolid, solidVsDynamic, friendly, true, maxSpeed, false){
	this->hp = maxHp;
	this->maxHp = maxHp;
	this->questAdded = false;
}

bool Creature::OnInteraction(Dynamic* secondDynamic) {
	cout << this->getName() << " interacting with " << secondDynamic->getName() << endl;
	return false;
}

void Creature::defend(int damage) { 
	this->hp -= damage; 
	cout << this->getName() << " attacked by " << damage << ". Health left: " << this->getHealth() << endl;
	if (hp < 0) {
		hp = 0;
		graphicState = GraphicState::DEATH;
	}

}

void Creature::heal(int quantityToHeal) { 
	this->hp = min(maxHp, hp + quantityToHeal); 
}

// <------------------------------------ Player --------------------------------------------->
cCreature_Player::cCreature_Player(string name, float px, float py) : Creature(name, "PackMan", px, py, 1, 1, 1, 100, 2.0f) {
};



// <------------------------------------ Fire Lady --------------------------------------------->
cCreature_FireLady::cCreature_FireLady(string name, float px, float py) : Creature(name, "FireLady", px, py, 1, 1, 1, 50, 1.5f) {  };

bool cCreature_FireLady::OnInteraction(Dynamic* secondDynamic) {
	//shared_ptr<cQuest> sharedQuest = make_shared<cQuest_FindThePinkRabbit>();
	if (!this->questAdded) {
		cQuest::addQuest(make_shared<cQuest_FindThePinkRabbit>());
		this->questAdded = true;
	}
	else
		cScriptProcessor::Get().AddCommand(new cCommand_Talk("Hi I am " + this->getName(), 1500, sf::Color::Red));
	return false;
}

// <------------------------------------ Earth Bender --------------------------------------------->
cCreature_EarthBender::cCreature_EarthBender(string name, float px, float py) : Creature(name, "EarthBender", px, py, 1, 1, 1, 50, 1.5f) {};

bool cCreature_EarthBender::OnInteraction(Dynamic* secondDynamic) {
	cScriptProcessor::Get().AddCommand(new cCommand_MoveTo(this, secondDynamic->getPosX() + 100, this->getPosY()));
	cScriptProcessor::Get().AddCommand(new cCommand_MoveTo(this, secondDynamic->getPosX() + 100, secondDynamic->getPosY()));
	cScriptProcessor::Get().AddCommand(new cCommand_MoveTo(this, secondDynamic->getPosX(), secondDynamic->getPosY()));
	cScriptProcessor::Get().AddCommand(new cCommand_Talk("Hi I am "+this->getName(), 1500, sf::Color::Color({ 200, 100, 0, 255 })));
	return false;
}


// <------------------------------------ Evil Rabbit --------------------------------------------->
cCreature_EvilRabbit::cCreature_EvilRabbit(string name, float px, float py) : Creature(name, "EvilRabbit", px, py, 1, 1, false, 50, 1.0f) {
	this->iAttack = 5;
	this->setWeapon(new cItem_Sword(20));
}

bool cCreature_EvilRabbit::OnInteraction(Dynamic* secondDynamic) {
	cScriptProcessor::Get().AddCommand(new cCommand_Talk("Cri Cri!", 1000, sf::Color::Red));
	//this->attack(((Creature*)secondDynamic), this->iAttack);
	return false;
}

void cCreature_EvilRabbit::updateAI(Dynamic* pPlayer) {
	float dx = this->getPosX() - pPlayer->getPosX();
	float dy = this->getPosY() - pPlayer->getPosY();
	float delta = sqrtf(dx * dx + dy * dy);

	if (framesOfRest == 0) {
		framesOfRest = 60 * 6;
		this->setAttacking(true);
	}

	if(framesOfRest > 60*4 && abs(delta) > Assets::get().GetSizeSprite())
		this->addVelocityNormalizedXY(-dx / delta, -dy / delta);

	framesOfRest--;
}

// <------------------------------------ Pink Friendly Rabbit --------------------------------------------->
cCreature_PinkRabbit::cCreature_PinkRabbit(string name, float px, float py) : Creature(name, "PinkRabbit", px, py, 1, 1, 1, 50, 1.0f) {};

bool cCreature_PinkRabbit::OnInteraction(Dynamic* secondDynamic) {
	cScriptProcessor::Get().AddCommand(new cCommand_Talk("Cri Cri!", 1000, sf::Color::Red));
	return false;
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
