#pragma once
#include "dynamic.h"
#include "textDrawer.h"

class Creature : public Dynamic {
protected:
	float hp;
	float maxHp;
	bool questAdded;
public:
	Creature();
	//~Creature();
	Creature(string name, string asset, float px, float py, bool solidVsSolid, bool solidVsDynamic, bool friendly, int maxHp, float maxSpeed);
	bool OnInteraction(Dynamic* secondDynamic);
	void updateAI(Creature* pPlayer) {};

	// Health
	void defend(Dynamic* collider);
	void heal(int quantityToHeal);
	inline int getHealth() { return hp; };
	inline int getMaxHealth() { return maxHp; };
	inline void increaseMaxHealth(int deltaMaxHp) { maxHp += deltaMaxHp; };

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

// <------------------------------------ Creature Enemy --------------------------------------------->
class cCreature_Enemy : public Creature {
public:
	cCreature_Enemy(string name, string asset, float px, float py);
	virtual bool OnInteraction(Dynamic* secondDynamic) override;
	virtual void updateAI(Dynamic* pPlayer);
protected:
	virtual void moveAI(Dynamic* pPlayer);
	virtual void fireAI(Dynamic* pPlayer);

protected:
	int framesOfRest;
	int framesCount;
	
};

// <------------------------------------ Evil Rabbit --------------------------------------------->
class cCreature_Enemy_Rabbit : public cCreature_Enemy {
public:
	cCreature_Enemy_Rabbit(string name, float px, float py);
};

// <------------------------------------ Evil Rabbito --------------------------------------------->
class cCreature_Enemy_Duelist : public cCreature_Enemy {
public:
	cCreature_Enemy_Duelist(string name, float px, float py);
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