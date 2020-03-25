#pragma once
#include "dynamic.h"

class Creature : public Dynamic {
private:
	int hp;
	int maxHp;
protected:
	bool questAdded;
public:
	Creature();
	//~Creature();
	Creature(string name, string asset, float px, float py, bool solidVsSolid, bool solidVsDynamic, bool friendly, int maxHp, float maxSpeed);
	inline void defend(int damage) { this->hp -= damage; }
	inline void attack(Creature* target, int damage) { target->defend(damage); cout << this->getName()  << " atacked " << target->getName() << " by " << damage << " HP" << endl; }
	bool OnInteraction(Dynamic* secondDynamic);
	void updateAI(Creature* pPlayer) {};
	inline void heal(int quantityToHeal) { this->hp = min(maxHp, hp + quantityToHeal); }

};

// <------------------------------------ Fire Lady --------------------------------------------->
class cCreature_FireLady : public Creature {
public:
	cCreature_FireLady(string name, float px, float py);
	bool OnInteraction(Dynamic* secondDynamic) override;
};

// <------------------------------------ Earth Bender --------------------------------------------->
class cCreature_EarthBender : public Creature {
public:
	cCreature_EarthBender(string name, float px, float py);
	bool OnInteraction(Dynamic* secondDynamic) override;
};

// <------------------------------------ Evil Rabbit --------------------------------------------->
class cCreature_EvilRabbit : public Creature {
public:
	cCreature_EvilRabbit(string name, float px, float py);
	bool OnInteraction(Dynamic* secondDynamic) override;
	void updateAI(Dynamic* pPlayer);
private:
	int iAttack;
	bool hasAtacked;
	int framesOfRest = 60 * 4;
};

// <------------------------------------ Pink Friendly Rabbit --------------------------------------------->
class cCreature_PinkRabbit : public Creature {
public:
	cCreature_PinkRabbit(string name, float px, float py);
	bool OnInteraction(Dynamic* secondDynamic) override;
	void updateAI(Dynamic* pPlayer);
private:
	int framesOfRest = 60 * 4;
};