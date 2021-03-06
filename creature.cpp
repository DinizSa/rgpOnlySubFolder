#include "creature.h"
#include "scriptProcessor.h"
#include "assets.h"
#include "quest.h"
#include "textDrawer.h"
#include "item.h"
#include "constants.h"
#include "projectile.h"

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
	this->iFramesCycle = 20;
}

bool Creature::OnInteraction(Dynamic* secondDynamic) {
	cout << "creature " << this->getName() << " interacting with " << secondDynamic->getName() << endl;
	return false;
}

void Creature::defend(Dynamic* collider) {
	if (!this->isBeingProjected()) {
		this->hp = max(this->hp - ((cProjectile*)collider)->getDamage(), 0.f);
		cout << this->getName() << " attacked by " << ((cProjectile*)collider)->getDamage() << ". Health left: " << this->getHealth() << endl;

		this->addVelocityNormalizedXY(collider->getMomentumX() * collider->getMaxSpeed() * collider->getWeight(), collider->getMomentumY() * collider->getMaxSpeed() * collider->getWeight());
		this->bInertia = true;
	}

	if (hp == 0) {
		graphicState = GraphicState::DEATH;
	}

}

void Creature::heal(int quantityToHeal) { 
	this->hp = min(maxHp, hp + quantityToHeal); 
}

// <------------------------------------ Player --------------------------------------------->
cCreature_Player::cCreature_Player(string name, float px, float py) : Creature(name, "PackMan", px, py, 1, 1, 1, 100, 1.0f) {
	//this->addItem(new cItem_Sword(10, 13, 4));
	//this->addItem(new cItem_EarthRing(10, 13, 4));
};



// <------------------------------------ Fire Lady --------------------------------------------->
cCreature_FireLady::cCreature_FireLady(string name, float px, float py) : Creature(name, "FireLady", px, py, 1, 1, 1, 50, 1.5f) {  };

bool cCreature_FireLady::OnInteraction(Dynamic* secondDynamic) {
	//shared_ptr<cQuest> sharedQuest = make_shared<cQuest_FindThePinkRabbit>();
	cScriptProcessor::Get().AddCommand(new cCommand_Talk(this->getName(), "Hi!", 120));
	return false;
}

// <------------------------------------ Earth Bender --------------------------------------------->
cCreature_EarthBender::cCreature_EarthBender(string name, float px, float py) : Creature(name, "EarthBender", px, py, 1, 1, 1, 50, 1.5f) {};

bool cCreature_EarthBender::OnInteraction(Dynamic* secondDynamic) {

	if (!this->questAdded && this->getName() == this->getName()) {
		auto quest = make_shared<cQuest_LearnEarthBending>();
		cQuest::addQuest(quest);
		this->questAdded = true;
		return true;
	}
	cScriptProcessor::Get().AddCommand(new cCommand_Talk(this->getName(), "Hi", 120));
	return false;
}

// <------------------------------------ cCreature_Enemy --------------------------------------------->
cCreature_Enemy::cCreature_Enemy(string name, string asset, float px, float py) : Creature(name, asset, px, py, 1, 1, false, 20, 1.0f) {
	// Default values
	this->setWeapon(new cItem_EarthRing(20, -1, -1));
	framesOfRest = 60 * 2;
	framesCount = 0;
}

bool cCreature_Enemy::OnInteraction(Dynamic* secondDynamic) {
	return false;
}

void cCreature_Enemy::moveAI(Dynamic* pPlayer) {

	float dx = this->getPosX() - pPlayer->getPosX();
	float dy = this->getPosY() - pPlayer->getPosY();
	float delta = sqrtf(dx * dx + dy * dy);

	if (framesCount > framesOfRest / 2 && abs(delta) > constants::ASSET_SIZE)
		this->addVelocityNormalizedXY(-dx / delta, -dy / delta);
}

void cCreature_Enemy::fireAI(Dynamic* pPlayer) {

	if (framesCount == framesOfRest) {
		this->setAttacking(true);
		framesCount = 0;
	}
}

void cCreature_Enemy::updateAI(Dynamic* pPlayer) {
	moveAI(pPlayer);
	fireAI(pPlayer);

	framesCount++;
}

// <------------------------------------ Evil Rabbit --------------------------------------------->
cCreature_Enemy_Rabbit::cCreature_Enemy_Rabbit(string name, float px, float py) : cCreature_Enemy(name, "EvilRabbit", px, py) {
	this->setWeapon(new cItem_EarthRing(20, -1,-1));
	framesOfRest = 60 * 2;
}

// <------------------------------------ Evil Swordsman --------------------------------------------->
cCreature_Enemy_Duelist::cCreature_Enemy_Duelist(string name, float px, float py) : cCreature_Enemy(name, "EarthBender", px, py) {
	this->setWeapon(new cItem_Sword(30, -1,-1));
	framesOfRest = 60 * 2;
}



// <------------------------------------ Pink Friendly Rabbit --------------------------------------------->
cCreature_PinkRabbit::cCreature_PinkRabbit(string name, float px, float py) : Creature(name, "PinkRabbit", px, py, 1, 1, 1, 50, 1.0f) {};

bool cCreature_PinkRabbit::OnInteraction(Dynamic* secondDynamic) {
	cScriptProcessor::Get().AddCommand( new cCommand_Talk("Cri Cri!", 100));
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
