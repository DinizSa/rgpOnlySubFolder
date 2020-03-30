#include "projectile.h"
#include "creature.h"

cProjectile::cProjectile(string name, string asset, float px, float py, float vectorDirectionX, float vectorDirectionY, bool friendly, float maxSpeed, float damage):
	Dynamic(name, asset, px, py, false, false, friendly, false, maxSpeed, true) {
	this->fVectorDirectionX = vectorDirectionX;
	this->fVectorDirectionY = vectorDirectionY;
	this->bEnergized = true;
	this->fDamage = damage;
	addVelocityNormalizedXY(this->fVectorDirectionX, this->fVectorDirectionY);
}
bool cProjectile::OnInteraction(Dynamic* secondDynamic) {
	if (secondDynamic->isFriendly() != this->isFriendly() ) { // If one is enemy of the other
		if (dynamic_cast<Creature*>(secondDynamic)) { // Is creature
			this->bEnergized = false;
			((Creature*)secondDynamic)->defend(this->getDamage()); // Inflic damage
			this->bEnergized = false;
			return true;
		}
	}
	return false;
}

void cProjectile::updateAI(Dynamic* pPlayer) {
}

// <--------------------------------------------- Fireball --------------------------------------------->
cProjectile_Fireball::cProjectile_Fireball(float px, float py, float vectorDirectionX, float vectorDirectionY, bool friendly, float damage): 
	cProjectile("Fireball", "fireball", px, py, vectorDirectionX, vectorDirectionY, friendly, 5.0f, damage) {
}