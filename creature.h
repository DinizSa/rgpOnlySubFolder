#pragma once
#include "dynamic.h"

class Creature : public Dynamic {
private:
	int hp;
	int maxHp;
public:
	Creature();
	~Creature();
	Creature(string name, float px, float py, bool solidVsSolid, bool solidVsDynamic, bool friendly, int maxHp, float maxSpeed);
	inline void defend(int damage) { this->hp -= damage; }
	inline void attack(Creature* target, int damage) { target->defend(damage); }
	void OnInteraction(Dynamic* secondDynamic);
};