#include "dynamic.h"
#include "assets.h"

Dynamic::Dynamic():
	Entity(){
	this->solidVsSolid = false;
	this->solidVsDynamic = false;
	this->friendly = true;
	this->vx = 0;
	this->vy = 0;
	this->hasFriction = true;
	this->maxSpeed = 0;
	facingDirection = SOUTH;
	graphicState = STANDING;
	msStartedMoving = 0;
	msSinceStartedMoving = 0;
}
Dynamic::~Dynamic() {
}
Dynamic::Dynamic(string name, float px, float py, float vx, float vy, float width, float height, bool solidVsSolid, bool solidVsDynamic, bool friendly, bool hasFriction, int maxSpeed) :
	Entity(name, px, py, width, height)	{\
	this->solidVsSolid = solidVsSolid;
	this->solidVsDynamic = solidVsDynamic;
	this->friendly = friendly;
	this->vx = vx;
	this->vy = vy;
	this->hasFriction = hasFriction;
	this->maxSpeed = maxSpeed;
	facingDirection = SOUTH;
	graphicState = STANDING;
	msStartedMoving = 0;
	msSinceStartedMoving = 0;
}
void Dynamic::update(Timer* timer, Maps* map, vector<Dynamic*>* vDynamic, int windowW, int windowH) {
	move(map, vDynamic, windowW, windowH);
	applyFriction();
	SetGraphics(timer);
}

void Dynamic::move(Maps* map, vector<Dynamic*>* vDynamic, int windowW, int windowH) {
	float widthLandscape = windowW / map->getNrHorizontal();
	float heightLandscape = windowH / map->getNrVertical();
	int blockXOrigin = (int)(px/ widthLandscape) % (int)widthLandscape;
	int blockXCenter = (int)((px+width/2)/ widthLandscape) % (int)widthLandscape;
	int blockXRight = (int)((px+width)/ widthLandscape) % (int)widthLandscape;
	int blockYOrigin= (int)(py/ heightLandscape) % (int)heightLandscape;
	int blockYCenter = (int)((py+height/2)/ heightLandscape) % (int)heightLandscape;
	int blockYDown = (int)((py+height)/ heightLandscape) % (int)heightLandscape;

	// Horizontal
	if ((vx > 0 && px < windowW - this->width && ( !this->solidVsSolid || (this->solidVsSolid && !map->getSolid(blockXRight, blockYCenter)))) && (!this->solidVsDynamic || (this->solidVsDynamic && !this->isCollidingDynamic(vDynamic, (int)(px + width), (int)(py + height/2)))) ||
		(vx < 0 && px > 0 && (!this->solidVsSolid || (this->solidVsSolid && !map->getSolid(blockXOrigin, blockYCenter))) && (!this->solidVsDynamic || (this->solidVsDynamic && !this->isCollidingDynamic(vDynamic, px, (int)(py+height/2) ))))) {
		px += vx;
	}
	// Vertical
	if ((vy > 0 && py < windowH - this->height && (!this->solidVsSolid || (this->solidVsSolid && !map->getSolid(blockXCenter, blockYDown ))) && (!this->solidVsDynamic || (this->solidVsDynamic && !this->isCollidingDynamic(vDynamic, (int)(px + width / 2), (int)(py + height))))) ||
		(vy < 0 && py > 0 && (!this->solidVsSolid || (this->solidVsSolid && !map->getSolid(blockXCenter, blockYOrigin))) && (!this->solidVsDynamic || (this->solidVsDynamic && !this->isCollidingDynamic(vDynamic, (int)(px + width / 2), py) )))) {
		py += vy;
	}

	this->shape.setPosition(px, py);
}

void Dynamic::SetGraphics(Timer* timer) {

	auto setTimeWalking = [&](FacingDirection direction) {
		if (facingDirection != direction) {
			facingDirection = direction;
			msStartedMoving = timer->getMsSinceStart();
			msSinceStartedMoving = 0;
		}
		else {
			msSinceStartedMoving = timer->getMsSinceStart() - msStartedMoving;
		}
	};

	if (vx > 0)
		setTimeWalking(FacingDirection::EAST);
	else if (vx < 0)
		setTimeWalking(FacingDirection::WEST);
	else if (vy > 0)
		setTimeWalking(FacingDirection::SOUTH);
	else if (vy < 0)
		setTimeWalking(FacingDirection::NORTH);

	if (vy == 0 && vx == 0)
		msSinceStartedMoving = 0;

	// phaseAnimation represents the collumn of the sprite
	int phaseAnimation = ((int)(msSinceStartedMoving / ((int)(this->maxSpeed * 50)))) % 3;
	int sizeSprite = Assets::get().GetSizeSprite(name);
	// facingDirection represents the line of the sprite
	setPartialTexture(phaseAnimation * sizeSprite, facingDirection * sizeSprite, sizeSprite, sizeSprite);
}


// Return a pointer to the entity that is colliding or nullptr if not colliding
Entity* Dynamic::getCollidingEntity(vector<Entity>* entitys) {
	for (Entity entity : *entitys)
	{
		if (this->getPosX() + this->getWidth() > entity.getPosX() && this->getPosX() < entity.getPosX() + entity.getWidth()) {
			if (this->getPosY() + this->getWidth() > entity.getPosY() && this->getPosY() < entity.getPosY() + entity.getHeight()) {
				cout << this->getName() << " colliding with " << entity.getName() << endl;
				return &entity;
			}
		}
	}
	return nullptr;
}

// Return a boolean if it's colliding (only if has different names)
bool Dynamic::isCollidingDynamic(vector<Dynamic*>* vDynamic, int posX, int posY) {
	for (int i =0; i < vDynamic->size(); i++)
	{
		if (this->getName() != (*vDynamic)[i]->getName()) {
			if (posX > (*vDynamic)[i]->getPosX() && posX < (*vDynamic)[i]->getPosX() + (*vDynamic)[i]->getWidth()) {
				if (posY > (*vDynamic)[i]->getPosY() && posY < (*vDynamic)[i]->getPosY() + (*vDynamic)[i]->getHeight()) {
					cout << this->getName() << "  colliding with " << (*vDynamic)[i]->getName() << endl;
					return true;
				}
			}
		}
	}
	return false;
}

// Return a pointer to the entity that is colliding or a nullptr if not colliding, in a chosen direction
// UP: 1, RIGHT: 2, DOWN:3, LEFT: 4
Entity* Dynamic::getCollidingEntity(vector<Entity>*, int direction) {
	return nullptr;
}


void Dynamic::applyFriction() {
	float friction = (float)maxSpeed/10.f;
	if (this->hasFriction) {
		// Horizontal
		if (abs(vx) < friction)
			vx = 0.f;
		if (vx > 0){
			vx -= friction;
			if (vx > this->maxSpeed)
				vx = this->maxSpeed;
		}else if (vx < 0) {
			vx += friction;
			if (vx < - this->maxSpeed)
				vx = -this->maxSpeed;
		}
		// Vertical
		if (abs(vy) < friction)
			vy = 0.f;
		if (vy > 0) {
			vy -= friction;
			if (vy > this->maxSpeed)
				vy = this->maxSpeed;
		}
		else if (vy < 0) {
			vy += friction;
			if (vy < -this->maxSpeed)
				vy = -this->maxSpeed;
		}
	}
}