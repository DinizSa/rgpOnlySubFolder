#include "dynamic.h"
#include "assets.h"

Dynamic::Dynamic():
	Entity(){
	this->solidVsSolid = false;
	this->solidVsDynamic = false;
	this->friendly = true;
	this->vx = 0.f;
	this->vy = 0.f;
	this->hasFriction = true;
	this->maxSpeed = 0;
	facingDirection = SOUTH;
	graphicState = STANDING;
	msStartedMoving = 0;
	msSinceStartedMoving = 0;
}
Dynamic::~Dynamic() {
}
Dynamic::Dynamic(string name, float px, float py, bool solidVsSolid, bool solidVsDynamic, bool friendly, bool hasFriction, float maxSpeed) :
	Entity(name, px, py)	{
	this->solidVsSolid = solidVsSolid;
	this->solidVsDynamic = solidVsDynamic;
	this->friendly = friendly;
	this->vx = 0.f;
	this->vy = 0.f;
	this->hasFriction = hasFriction;
	this->maxSpeed = maxSpeed;
	facingDirection = SOUTH;
	graphicState = STANDING;
	msStartedMoving = 0;
	msSinceStartedMoving = 0;
}
void Dynamic::update(Timer* timer, Maps* map, vector<Dynamic*>* vDynamic) {
	move(map, vDynamic, 800, 600);
	applyFriction();
	SetGraphics(timer);
}

void Dynamic::move(Maps* map, vector<Dynamic*>* vDynamic, int windowW, int windowH) {
	// Margin around the rectangle that is not considered in the colision, so it looks smoother
	float marginEmpty = 0.15f;
	float widthLandscape = windowW / map->getNrHorizontal();
	float heightLandscape = windowH / map->getNrVertical();
	int blockXOrigin = (int)((px + width * marginEmpty)/ widthLandscape) % (int)widthLandscape;
	int blockXCenter = (int)((px + width/2)/ widthLandscape) % (int)widthLandscape;
	int blockXRight = (int)((px + width * (1.f- marginEmpty))/ widthLandscape) % (int)widthLandscape;
	int blockYOrigin= (int)((py + height * marginEmpty) / heightLandscape) % (int)heightLandscape;
	int blockYCenter = (int)((py+height/2)/ heightLandscape) % (int)heightLandscape;
	int blockYDown = (int)((py+ height * (1.f - marginEmpty))/ heightLandscape) % (int)heightLandscape;

	// Horizontal
	if ((vx > 0 && px < windowW - this->width && ( !this->solidVsSolid || (this->solidVsSolid && !map->getSolid(blockXRight, blockYCenter)))) && (!this->solidVsDynamic || (this->solidVsDynamic && !this->isCollidingDynamic(vDynamic, (int)(px + width* (1.f - marginEmpty)), (int)(py + height/2)))) ||
		(vx < 0 && px > 0 && (!this->solidVsSolid || (this->solidVsSolid && !map->getSolid(blockXOrigin, blockYCenter))) && (!this->solidVsDynamic || (this->solidVsDynamic && !this->isCollidingDynamic(vDynamic, px + width * marginEmpty, (int)(py+height/2) ))))) {
		px += vx;
	}
	else {
		vx = 0;
	}
	// Vertical
	if ((vy > 0 && py < windowH - this->height && (!this->solidVsSolid || (this->solidVsSolid && !map->getSolid(blockXCenter, blockYDown ))) && (!this->solidVsDynamic || (this->solidVsDynamic && !this->isCollidingDynamic(vDynamic, (int)(px + width / 2), (int)(py + height))))) ||
		(vy < 0 && py > 0 && (!this->solidVsSolid || (this->solidVsSolid && !map->getSolid(blockXCenter, blockYOrigin))) && (!this->solidVsDynamic || (this->solidVsDynamic && !this->isCollidingDynamic(vDynamic, (int)(px + width / 2), py) )))) {
		py += vy;
	}
	else {
		vy = 0;
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
	int phaseAnimation = 0;
	if(this->maxSpeed > 0)
		phaseAnimation = ((int)(msSinceStartedMoving * (this->maxSpeed / 50.f))) % 3;

	int sizeSprite = Assets::get().GetSizeSprite(name);
	// facingDirection represents the line of the sprite
	setPartialTexture(phaseAnimation * sizeSprite, facingDirection * sizeSprite, sizeSprite, sizeSprite);

}


// Return a pointer to the entity that is colliding or nullptr if not colliding 
Dynamic* Dynamic::getCollidingDynamic(vector<Dynamic*>* vDynamic) {
	for (unsigned i = 0; i < vDynamic->size(); i++)
	{
		if (this != (*vDynamic)[i]) {
			if (this->getPosX() + this->getWidth() > (*vDynamic)[i]->getPosX() && this->getPosX() < (*vDynamic)[i]->getPosX() + (*vDynamic)[i]->getWidth()) {
				if (this->getPosY() + this->getWidth() > (*vDynamic)[i]->getPosY() && this->getPosY() < (*vDynamic)[i]->getPosY() + (*vDynamic)[i]->getHeight()) {
					//cout << this->getName() << " colliding with " << (*vDynamic)[i]->getName() << endl;
					return (*vDynamic)[i];
				}
			}
		}
	}
	return nullptr;
}

// Return a boolean if it's colliding
bool Dynamic::isCollidingDynamic(vector<Dynamic*>* vDynamic, float posX, float posY) {
	for (unsigned i =0; i < vDynamic->size(); i++)
	{
		if (this != (*vDynamic)[i]) {
			if (posX > (*vDynamic)[i]->getPosX() && posX < (*vDynamic)[i]->getPosX() + (*vDynamic)[i]->getWidth()) {
				if (posY > (*vDynamic)[i]->getPosY() && posY < (*vDynamic)[i]->getPosY() + (*vDynamic)[i]->getHeight()) {
					//cout << this->getName() << "  colliding with " << (*vDynamic)[i]->getName() << endl;
					return true;
				}
			}
		}
	}
	return false;
}



void Dynamic::applyFriction() {
	float friction = maxSpeed/20.f;
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