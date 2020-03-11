#pragma once
#include "dynamic.h"

class Creature : public Dynamic {
private:
	int hp;
	int maxHp;
public:
	Creature();
	//~Creature();
	Creature(string name, float px, float py, bool solidVsSolid, bool solidVsDynamic, bool friendly, int maxHp, float maxSpeed);
	inline void defend(int damage) { this->hp -= damage; }
	inline void attack(Creature* target, int damage) { target->defend(damage); }
	void OnInteraction(Dynamic* secondDynamic);
	void updateAI(Creature* pPlayer) {};

};

// <------------------------------------ Fire Lady --------------------------------------------->
class cCreature_FireLady : public Creature {
public:
	cCreature_FireLady(float px, float py);
	void OnInteraction(Dynamic* secondDynamic) override;
};

// <------------------------------------ Earth Bender --------------------------------------------->
class cCreature_EarthBender : public Creature {
public:
	cCreature_EarthBender(float px, float py);
	void OnInteraction(Dynamic* secondDynamic) override;
};

// <------------------------------------ Evil Rabbit --------------------------------------------->
class cCreature_EvilRabbit : public Creature {
public:
	cCreature_EvilRabbit(float px, float py);
	void OnInteraction(Dynamic* secondDynamic) override;
	void updateAI(Dynamic* pPlayer);
private:
	int framesOfRest = 60 * 4;
};

// <------------------------------------ Pink Friendly Rabbit --------------------------------------------->
class cCreature_PinkRabbit : public Creature {
public:
	cCreature_PinkRabbit(float px, float py);
	void OnInteraction(Dynamic* secondDynamic) override;
	void updateAI(Dynamic* pPlayer);
private:
	int framesOfRest = 60 * 4;
};