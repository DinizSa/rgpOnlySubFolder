#pragma once
using namespace std;
#include "entity.h"
#include <string>
#include "maps.h"
#include "timer.h"
#include <memory>
#include <vector>

class Dynamic: public Entity {
protected:
	bool isBeingProjected();
	float vx, vy;
	bool solidVsSolid;
	bool solidVsDynamic;
	bool friendly;
	bool hasFriction;
	float maxSpeed;
	enum FacingDirection{SOUTH = 0, WEST = 1, NORTH = 2, EAST = 3} facingDirection;
	int phaseAnimation;
	enum GraphicState {STANDING, WALKING, DEATH} graphicState;
	vector< Dynamic*> vInventory;
	Dynamic* weapon;
	bool bProjetile;
	int iFramesPassed;
	int iFramesCycle;
	bool bInertia;
	

public:
	Dynamic();
	Dynamic(string name, string asset, float px, float py, bool solidVsSolid, bool solidVsDynamic, bool friendly, bool hasFriction, float maxSpeed, bool isProjetile);
	~Dynamic();
	void addVelocityNormalizedX(float deltaVx);
	void addVelocityNormalizedY(float deltaVy);
	void addVelocityNormalizedXY(float deltaVx, float deltaVy);
	void setVelocityNormalizedXY(float deltaVx, float deltaVy);
	inline void resetVelocity() { this->vx = 0.f; this->vy = 0.f; }
	virtual bool OnInteraction(Dynamic* secondDynamic) = 0;
	Dynamic* getCollidingFront(vector<Dynamic*>* vDynamic);
	bool isCollidingPlayer(Dynamic* pPlayer);
	Dynamic* getColliding(vector<Dynamic*> dynamics);
	void update(Timer* timer, Maps* map, vector<Dynamic*>* vDynamic);
	virtual void updateAI(Dynamic* pPlayer) {};

	// Getters
	inline float getSolidVsSolid() { return this->solidVsSolid; }
	inline float getSolidVsDynamic() { return this->solidVsDynamic; }
	inline float isFriendly() { return this->friendly; }
	inline float getMaxSpeed() { return this->maxSpeed; }
	inline string getName() { return this->sName; }
	inline int getFacingDirection() { return facingDirection; }
	void setFacingDirection(int facingDirection);
	inline float getVelX() { return this->vx; }
	inline float getVelY() { return this->vy; }
	inline bool isProjectile() { return bProjetile; }
	inline bool isAttacking() { return this->bAttacking; }
	inline void setAttacking(bool attacking) { this->bAttacking = attacking;}
	float getMomentumX();
	float getMomentumY();
	virtual void SetGraphics();
	virtual void setFrame();

	// Weapons
	inline void setWeapon(Dynamic* weapon) { this->weapon = weapon; }
	inline bool hasWeaponEquiped() { return this->weapon != nullptr; };
	Dynamic* attackWeapon();

	// Inventory
	void consumeItem(string itemName, int quantity);
	void addItem(Dynamic* itemToAdd);
	bool hasItem(Dynamic* itemToCheck);
	inline vector< Dynamic*>* getAllItems() { return &vInventory;  }

private:
	void move(Maps* map, vector<Dynamic*>* vDynamic);
	bool isCollidingDynamic(vector<Dynamic*>* entitys, float posX, float posY);
	void applyFriction();
	int msStartedMoving;
	int msSinceStartedMoving;
	string sName;
	bool bAttacking;
};