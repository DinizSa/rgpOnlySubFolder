#include "creature.h"

Creature::Creature(): Dynamic() {
	hp = 0;
	maxHp = 0;
}
Creature::~Creature() {
}
Creature::Creature(string name, float px, float py, bool solidVsSolid, bool solidVsDynamic, bool friendly, int maxHp, int maxSpeed):
	Dynamic(name, px, py, solidVsSolid, solidVsDynamic, friendly, true, maxSpeed){
	this->hp = maxHp;
	this->maxHp = maxHp;
}

void Creature::OnInteraction(Dynamic* secondDynamic) {
	cout << this->name << " interacting with " << secondDynamic->getName() << endl;
}



