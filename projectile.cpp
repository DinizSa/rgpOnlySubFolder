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
	this->iFramesShow = constants::FPS * 10;
	this->hasHitted = false;
	addVelocityNormalizedXY(this->fVectorDirectionX, this->fVectorDirectionY);
}
bool cProjectile::OnInteraction(Dynamic* secondDynamic) {

	if (secondDynamic->isFriendly() != this->isFriendly() && !hasHitted) { // If one is enemy of the other
		hasHitted = true;
		if (dynamic_cast<Creature*>(secondDynamic)) { // Is creature
			this->bEnergized = false;
			((Creature*)secondDynamic)->defend(this->getDamage()); // Inflic damage
			return true;
		}
	}
	return false;
}

// Check if has projectile has expired
void cProjectile::checkDurability()
{
	this->iFramesShow--;
	if (this->iFramesShow < 0)
		this->setEnergized(false);
}


// <--------------------------------------------- Fireball --------------------------------------------->
cProjectile_Fireball::cProjectile_Fireball(float px, float py, float vectorDirectionX, float vectorDirectionY, bool friendly, float damage): 
	cProjectile("Fireball", "fireball", px, py, vectorDirectionX, vectorDirectionY, friendly, 5.0f, damage) {
	iFramesShow = constants::FPS / 2;
}

void cProjectile_Fireball::updateAI(Dynamic* pPlayer) {
	if (this->getVelX() == 0 && this->getVelY() == 0) {
		this->bEnergized = false;
	}
	this->checkDurability();
}

// <--------------------------------------------- Sword --------------------------------------------->
cProjectile_Sword::cProjectile_Sword(float px, float py, float vectorDirectionX, float vectorDirectionY, bool friendly, float damage) :
	cProjectile("Sword", "Sword4", px, py , vectorDirectionX, vectorDirectionY, friendly, 5.0f, damage) {
	this->iFramesShow = constants::FPS / 2;
}

bool cProjectile_Sword::OnInteraction(Dynamic* secondDynamic) {
	if (secondDynamic->isFriendly() != this->isFriendly() && !hasHitted) { // If one is enemy of the other
		hasHitted = true;
		if (dynamic_cast<Creature*>(secondDynamic) ) { // Is creature
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

	checkDurability();
	
}