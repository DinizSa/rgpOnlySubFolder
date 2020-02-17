#include "creature.h"

Creature::Creature(): Dynamic() {
	hp = 0;
	maxHp = 0;
}
Creature::~Creature() {
}
Creature::Creature(string name, float px, float py, float vx, float vy, float width, float height, bool solidVsSolid, bool solidVsDynamic, bool friendly, int maxHp, int maxSpeed):
	Dynamic(name, px, py, vx, vy, width, height, solidVsSolid, solidVsDynamic, friendly, true, maxSpeed){
	this->hp = maxHp;
	this->maxHp = maxHp;
}

void Creature::OnInteraction(Dynamic* secondDynamic) {
	cout << this->name << " interacting with " << secondDynamic->getName() << endl;
}



