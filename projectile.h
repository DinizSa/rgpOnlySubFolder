#pragma once
#include "dynamic.h"
#include "timer.h"

class cProjectile : public Dynamic {
public:
	cProjectile(string name, string asset, float px, float py, float vectorDirectionX, float vectorDirectionY, bool friendly, float maxSpeed, float damage);
	void updateAI(Dynamic* pPlayer) override = 0;
	inline bool isEnergized() { return bEnergized; }
	inline void setEnergized(bool energized) { this->bEnergized = energized; }
	virtual bool OnInteraction(Dynamic* secondDynamic) override;
	inline float getDamage() { return fDamage; };
	void checkDurability();
	void setFrame() override;


protected:
	float fVectorDirectionX;
	float fVectorDirectionY;
	bool bEnergized;
	float fDamage;
	int iFramesDuration;
	bool hasHitted;
};

// <--------------------------------------------- Fireball projectile --------------------------------------------->
class cProjectile_Fireball : public cProjectile {
public: 
	cProjectile_Fireball(float px, float py, float vectorDirectionX, float vectorDirectionY, bool friendly, float damage);
	void updateAI(Dynamic* pPlayer) override;
};

// <--------------------------------------------- Sword projectile --------------------------------------------->
class cProjectile_Sword : public cProjectile {
public:
	cProjectile_Sword(float px, float py, float vectorDirectionX, float vectorDirectionY, bool friendly, float damage);
	void updateAI(Dynamic* pPlayer) override;
	bool OnInteraction(Dynamic* secondDynamic) override;
};

