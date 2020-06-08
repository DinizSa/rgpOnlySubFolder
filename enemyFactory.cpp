#include "enemyFactory.h"

enemyFactory::enemyFactory() {
}

Creature* enemyFactory::getEnemy(int posX, int posY) {
	int random = rand() % 2;

	switch (random)
	{
	case 0:
		return new cCreature_Enemy_Duelist("Carlos", posX, posY);
		break;
	case 1:
		return new cCreature_Enemy_Rabbit("Rabbit", posX, posY);
		break;
	default:
		break;
	}
}