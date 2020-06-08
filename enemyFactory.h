#pragma once
#include "creature.h"

class enemyFactory {
public:
	static Creature* getEnemy(int posX, int posY);

private:
	enemyFactory();
};