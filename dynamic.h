#pragma once
using namespace std;
#include "entity.h"
#include <string>
#include "maps.h"
#include "timer.h"

class Dynamic: public Entity {
protected:
	float vx, vy;
	bool solidVsSolid;
	bool solidVsDynamic;
	bool friendly;
	bool hasFriction;
	int maxSpeed;
	enum FacingDirection{SOUTH = 0, WEST = 1, NORTH = 2, EAST = 3} facingDirection;
	enum {STANDING, WALKING, DEATH} graphicState;

public:
	Dynamic();
	Dynamic(string name, float px, float py, bool solidVsSolid, bool solidVsDynamic, bool friendly, bool hasFriction, int maxSpeed);
	~Dynamic();
	inline void addVelocityNormalizedX(float deltaVx) { this->vx += deltaVx; }
	inline void addVelocityNormalizedY(float deltaVy) { this->vy += deltaVy; }
	inline void addVelocityNormalizedXY(float deltaVx, float deltaVy) { this->vx += deltaVx * maxSpeed; this->vy += deltaVy * maxSpeed; }
	inline void resetVelocity() { this->vx = 0.f; this->vy = 0.f; }
	virtual void OnInteraction(Dynamic* secondDynamic) = 0;
	Dynamic* getCollidingDynamic(vector<Dynamic*>* vDynamic);
	void update(Timer* timer, Maps* map, vector<Dynamic*>* vDynamic);

	// Getters
	inline float getSolidVsSolid() { return this->solidVsSolid; }
	inline float getSolidVsDynamic() { return this->solidVsDynamic; }
	inline float isFriendly() { return this->friendly; }
	inline int getMaxSpeed() { return this->maxSpeed; }

private:
	void move(Maps* map, vector<Dynamic*>* vDynamic, int windowW, int windowH);
	bool isCollidingDynamic(vector<Dynamic*>* entitys, int posX, int posY);
	void applyFriction();
	void SetGraphics(Timer* timer);
	int msStartedMoving;
	int msSinceStartedMoving;

};