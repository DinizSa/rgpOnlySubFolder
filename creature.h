#pragma once
#include "dynamic.h"
#include "textDrawer.h"

class Creature : public Dynamic {
protected:
	int hp;
	int maxHp;
protected:
	bool questAdded;
public:
	Creature();
	//~Creature();
	Creature(string name, string asset, float px, float py, bool solidVsSolid, bool solidVsDynamic, bool friendly, int maxHp, float maxSpeed);
	bool OnInteraction(Dynamic* secondDynamic);
	void updateAI(Creature* pPlayer) {};

	// Health
	inline void attack(Creature* target, int damage) { target->defend(damage); }
	void defend(int damage);
	void heal(int quantityToHeal);
	inline int getHealth() { return hp; };
	inline int getMaxHealth() { return maxHp; };

};


// <------------------------------------ Player --------------------------------------------->
class cCreature_Player : public Creature {
public:
	cCreature_Player(string name, float px, float py);
	inline bool OnInteraction(Dynamic* secondDynamic) override { return false; };
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