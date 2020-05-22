#include "projectile.h"
#include "creature.h"
#include "constants.h"
#include <stdlib.h> 

cProjectile::cProjectile(string name, string asset, float px, float py, float vectorDirectionX, float vectorDirectionY, bool friendly, float maxSpeed, float damage):
	Dynamic(name, asset, px, py, true, false, friendly, false, maxSpeed, true) {
	this->fVectorDirectionX = vectorDirectionX;
	this->fVectorDirectionY = vectorDirectionY;
	this->bEnergized = true;
	this->fDamage = damage;
	iTargetsHitted = 0;
	iTargetsMax = 1;
	addVelocityNormalizedXY(this->fVectorDirectionX, this->fVectorDirectionY);
}
bool cProjectile::OnInteraction(Dynamic* secondDynamic) {

	if (secondDynamic->isFriendly() != this->isFriendly() ) { // If one is enemy of the other
		if (dynamic_cast<Creature*>(secondDynamic) && iTargetsHitted < iTargetsMax) { // Is creature
			this->bEnergized = false;
			iTargetsHitted++;
			((Creature*)secondDynamic)->defend(this->getDamage()); // Inflic damage
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

void cProjectile_Fireball::updateAI(Dynamic* pPlayer) {
	if (this->getVelX() == 0 && this->getVelY() == 0) {
		this->bEnergized = false;
	}
}

// <--------------------------------------------- Sword --------------------------------------------->
cProjectile_Sword::cProjectile_Sword(float px, float py, float vectorDirectionX, float vectorDirectionY, bool friendly, float damage) :
	cProjectile("Sword", "Sword4", px, py , vectorDirectionX, vectorDirectionY, friendly, 5.0f, damage) {
	this->framesLeft = 30;
	iTargetsMax = 1;
}

bool cProjectile_Sword::OnInteraction(Dynamic* secondDynamic) {
	if (secondDynamic->isFriendly() != this->isFriendly()) { // If one is enemy of the other
		if (dynamic_cast<Creature*>(secondDynamic) && iTargetsHitted < iTargetsMax) { // Is creature
			iTargetsHitted++;
			((Creature*)secondDynamic)->defend(this->getDamage()); // Inflic damage
			return true;
		}
	}
	return false;
}

void cProjectile_Sword::updateAI(Dynamic* pPlayer) {
	// Velocity setted just so the direction frame is setted
	this->setVelocityNormalizedXY(pPlayer->getVelX(), pPlayer->getVelY() );
	this->setPosX(pPlayer->getPosX() + pPlayer->getMomentumX() * (float)constants::ASSET_SIZE * 0.5f);
	this->setPosY(pPlayer->getPosY() + pPlayer->getMomentumY() * (float)constants::ASSET_SIZE * 0.5f);
	
	if (getVelX() == 0 && getVelY() == 0)
		this->setFacingDirection(pPlayer->getFacingDirection());

	
	this->framesLeft--;
	if (this->framesLeft < 0)
		this->setEnergized(false);
}