#pragma once
using namespace std;
#include "entity.h"
#include <string>
#include "maps.h"
#include "timer.h"
#include <memory>

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
	map< Dynamic*, int> lInventory;

public:
	Dynamic();
	Dynamic(string name, string asset, float px, float py, bool solidVsSolid, bool solidVsDynamic, bool friendly, bool hasFriction, float maxSpeed);
	~Dynamic();
	inline void addVelocityNormalizedX(float deltaVx) { this->vx += deltaVx; }
	inline void addVelocityNormalizedY(float deltaVy) { this->vy += deltaVy; }
	inline void addVelocityNormalizedXY(float deltaVx, float deltaVy) { this->vx += deltaVx * maxSpeed; this->vy += deltaVy * maxSpeed; }
	inline void resetVelocity() { this->vx = 0.f; this->vy = 0.f; }
	virtual bool OnInteraction(Dynamic* secondDynamic) = 0;
	Dynamic* getCollidingDynamic(vector<Dynamic*>* vDynamic);
	bool isCollidingPlayer(Dynamic* pPlayer);
	void update(Timer* timer, Maps* map, vector<Dynamic*>* vDynamic);
	virtual void updateAI(Dynamic* pPlayer) {};

	// Getters
	inline float getSolidVsSolid() { return this->solidVsSolid; }
	inline float getSolidVsDynamic() { return this->solidVsDynamic; }
	inline float isFriendly() { return this->friendly; }
	inline float getMaxSpeed() { return this->maxSpeed; }
	inline string getName() { return this->sName; }

	// Inventory
	void addItem(Dynamic* itemToAdd, int quantity);
	void removeItem(Dynamic* itemToRemove, int quantity);
	bool hasItem(Dynamic* itemToCheck);

private:
	void move(Maps* map, vector<Dynamic*>* vDynamic, int windowW, int windowH);
	bool isCollidingDynamic(vector<Dynamic*>* entitys, float posX, float posY);
	void applyFriction();
	void SetGraphics(Timer* timer);
	int msStartedMoving;
	int msSinceStartedMoving;
	string sName;
};