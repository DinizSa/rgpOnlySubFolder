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
	float vx, vy;
	bool solidVsSolid;
	bool solidVsDynamic;
	bool friendly;
	bool hasFriction;
	float maxSpeed;
	enum FacingDirection{SOUTH = 0, WEST = 1, NORTH = 2, EAST = 3} facingDirection;
	enum GraphicState {STANDING, WALKING, DEATH} graphicState;
	vector< Dynamic*> vInventory;
	Dynamic* weapon;
	bool bProjetile;
	

public:
	Dynamic();
	Dynamic(string name, string asset, float px, float py, bool solidVsSolid, bool solidVsDynamic, bool friendly, bool hasFriction, float maxSpeed, bool isProjetile);
	~Dynamic();
	inline void addVelocityNormalizedX(float deltaVx) { this->vx += deltaVx; }
	inline void addVelocityNormalizedY(float deltaVy) { this->vy += deltaVy; }
	inline void addVelocityNormalizedXY(float deltaVx, float deltaVy) { this->vx += deltaVx * maxSpeed; this->vy += deltaVy * maxSpeed; }
	inline void setVelocityNormalizedXY(float deltaVx, float deltaVy) { this->vx = deltaVx; this->vy = deltaVy; }
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
	inline int geFacingDirection() { return facingDirection; }
	inline float getVelX() { return this->vx; }
	inline float getVelY() { return this->vy; }
	inline bool isProjectile() { return bProjetile; }
	// Weapons
	inline void setWeapon(Dynamic* weapon) { this->weapon = weapon; }
	inline bool hasWeaponEquiped() { return this->weapon != nullptr; };
	Dynamic* attackWeapon();

	// Inventory
	void consumeItem(Dynamic* itemToAdd, int quantity);
	void addItem(Dynamic* itemToAdd);
	bool hasItem(Dynamic* itemToCheck);
	inline vector< Dynamic*>* getAllItems() { return &vInventory;  }

private:
	void move(Maps* map, vector<Dynamic*>* vDynamic, int windowW, int windowH);
	bool isCollidingDynamic(vector<Dynamic*>* entitys, float posX, float posY);
	void applyFriction();
	void SetGraphics(Timer* timer);
	int msStartedMoving;
	int msSinceStartedMoving;
	string sName;
};