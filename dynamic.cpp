#include "dynamic.h"
#include "assets.h"
#include "quest.h"
#include "item.h"
#include "scriptProcessor.h"
#include "constants.h"

Dynamic::Dynamic():
	Entity(){
	this->solidVsSolid = false;
	this->solidVsDynamic = false;
	this->friendly = true;
	this->vx = 0.f;
	this->vy = 0.f;
	this->hasFriction = true;
	this->maxSpeed = 0;
	facingDirection = FacingDirection::SOUTH;
	graphicState = GraphicState::STANDING;
	msStartedMoving = 0;
	msSinceStartedMoving = 0;
	this->sName = "";
	this->weapon = nullptr;
	this->bProjetile = false;
	this->iFramesPassed = 0;
	this->iFramesCycle = 30;
	bInertia = false;
	phaseAnimation = 0;
	fWeight = 0.f;
}
Dynamic::~Dynamic() {
	for (auto item : vInventory) {
		delete item;
	}
 }

Dynamic::Dynamic(string name, string asset, float px, float py, bool solidVsSolid, bool solidVsDynamic, bool friendly, bool hasFriction, float maxSpeed, bool isProjetile) :
	Entity(asset, px, py)	{
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
	this->sName = name;
	this->weapon = nullptr;
	this->bProjetile = isProjetile;
	this->iFramesPassed = 0;
	this->iFramesCycle = 30;
	bInertia = false;
	phaseAnimation = 0;
	fWeight = 1.f;
}
void Dynamic::update(Timer* timer, Maps* map, vector<Dynamic*>* vDynamic) {
	if (graphicState != GraphicState::DEATH) {
		move(map, vDynamic);
		if (cScriptProcessor::Get().getUserControlEnabled())
			updateAI((*vDynamic)[0]);
		applyFriction();
		SetGraphics();
	}
	else {
		this->solidVsDynamic = false;
		this->solidVsSolid = false;
		setDeathGraphics();
	}

}


void Dynamic::addVelocityNormalizedX(float deltaVx) { 
	if (!isBeingProjected()) {
		this->vx += deltaVx; 
	} 
}
void Dynamic::addVelocityNormalizedY(float deltaVy) { 
	if (!isBeingProjected()) {
		this->vy += deltaVy; 
	} 
}
void Dynamic::addVelocityNormalizedXY(float deltaVx, float deltaVy) { 
	if (!isBeingProjected()) {
	this->vx += deltaVx * maxSpeed; this->vy += deltaVy * maxSpeed;
	} 
}
void Dynamic::setVelocityNormalizedXY(float deltaVx, float deltaVy) { 
	if (!isBeingProjected()) {
		this->vx = deltaVx; this->vy = deltaVy; 
	} 
}

void Dynamic::move(Maps* map, vector<Dynamic*>* vDynamic) {
	const int mapPixelsW = map->getNrHorizontal() * constants::ASSET_SIZE;
	const int mapPixelsH = map->getNrVertical() * constants::ASSET_SIZE;
	// Margin around the rectangle that is not considered in the colision, so it looks smoother
	float marginEmptyX = 0.30f;
	float marginEmptyY = 0.10f;
	float widthLandscape = constants::ASSET_SIZE; // MAP_WIDTH / map->getNrHorizontal();
	float heightLandscape = constants::ASSET_SIZE; //MAP_HEIGHT / map->getNrVertical();
	int blockXOrigin = (int)((px + width * marginEmptyX)/ widthLandscape) % (int)widthLandscape;
	int blockXCenter = (int)((px + width/2)/ widthLandscape) % (int)widthLandscape;
	int blockXRight = (int)((px + width * (1.f- marginEmptyX))/ widthLandscape) % (int)widthLandscape;
	int blockYOrigin= (int)((py + height * marginEmptyY) / heightLandscape) % (int)heightLandscape;
	int blockYCenter = (int)((py+height/2)/ heightLandscape) % (int)heightLandscape;
	int blockYDown = (int)((py+ height * (1.f - marginEmptyY))/ heightLandscape) % (int)heightLandscape;

	// Horizontal
	if ((vx > 0 && px < mapPixelsW - this->width && ( !this->solidVsSolid || (this->solidVsSolid && !map->getSolid(blockXRight, blockYCenter)))) && (!this->solidVsDynamic || (this->solidVsDynamic && !this->isCollidingDynamic(vDynamic, (px + width* (1.f - marginEmptyX)), (py + height/2)))) ||
		(vx < 0 && px > 0 && (!this->solidVsSolid || (this->solidVsSolid && !map->getSolid(blockXOrigin, blockYCenter))) && (!this->solidVsDynamic || (this->solidVsDynamic && !this->isCollidingDynamic(vDynamic, px + width * marginEmptyX, (py+height/2) ))))) {
		px += vx;
	}
	else{
		if (vx < 0)
			facingDirection = WEST;
		else if (vx > 0)
			facingDirection = EAST;
		if (this->isProjectile() && vx != 0)
			vy = 0;
		vx = 0;
	}
	// Vertical
	if ((vy > 0 && py < mapPixelsH - this->height && (!this->solidVsSolid || (this->solidVsSolid && !map->getSolid(blockXCenter, blockYDown ))) && (!this->solidVsDynamic || (this->solidVsDynamic && !this->isCollidingDynamic(vDynamic,(px + width / 2), (py + height * (1.f - marginEmptyY)))))) ||
		(vy < 0 && py > 0 && (!this->solidVsSolid || (this->solidVsSolid && !map->getSolid(blockXCenter, blockYOrigin))) && (!this->solidVsDynamic || (this->solidVsDynamic && !this->isCollidingDynamic(vDynamic, (px + width / 2), py + height * marginEmptyY) )))) {
		py += vy;
	}
	else{
		if (vy < 0)
			facingDirection = NORTH;
		else if (vy > 0)
			facingDirection = SOUTH;
		if (this->isProjectile() && vy != 0)
			vx = 0;
		vy = 0;
	}


	this->shape.setPosition(px, py);
}

void Dynamic::setFrame() {

	if (vy == 0 && vx == 0)
		iFramesPassed == 0;
	else
		iFramesPassed++;
	if (iFramesPassed >= iFramesCycle)
		iFramesPassed == 0;
	
}

bool Dynamic::isBeingProjected() {
	if (bInertia && vy == 0 && vx == 0) {
		bInertia = false;
	}
	return bInertia;
}

void Dynamic::SetGraphics() {

	setFrame();

	if (!isBeingProjected()) {
		phaseAnimation = 0;
		if (this->maxSpeed > 0)
			phaseAnimation = (int)((int)(iFramesPassed / (iFramesCycle / 3)) % 3);

		// facingDirection represents the line of the sprite
		if (vx > 0)
			facingDirection = FacingDirection::EAST;
		else if (vx < 0)
			facingDirection = FacingDirection::WEST;
		else if (vy > 0)
			facingDirection = FacingDirection::SOUTH;
		else if (vy < 0)
			facingDirection = FacingDirection::NORTH;

	}
	
	setPartialTexture(phaseAnimation * constants::ASSET_SIZE, facingDirection * constants::ASSET_SIZE, constants::ASSET_SIZE, constants::ASSET_SIZE);

}

void Dynamic::setFacingDirection(int facingDirection) {
	switch (facingDirection)
	{
	case 0: // South
		this->facingDirection = FacingDirection::SOUTH;
		break;
	case 1: // West
		this->facingDirection = FacingDirection::WEST;
		break;
	case 2: // North
		this->facingDirection = FacingDirection::NORTH;
		break;
	case 3: // East
		this->facingDirection = FacingDirection::EAST;
		break;
	default:
		break;
	}
}

float Dynamic::getMomentumX() { 
	float momentumX;
	switch (this->getFacingDirection())
	{
	case 1: // West
		momentumX = -1.f;
		break;
	case 3: // East
		momentumX = 1.f;
		break;
	default:
		momentumX = 0.f;
		break;
	}
	return momentumX + (vx / maxSpeed) / 3;
};

float Dynamic::getMomentumY() {
	float momentumY;
	switch (this->getFacingDirection())
	{
	case 0: // South
		momentumY = 1.f;
		break;
	case 2: // North
		momentumY = -1.f;
		break;
	default:
		momentumY = 0.f;
		break;
	}
	return momentumY + (vy / maxSpeed) / 3;
};

// Return a pointer to the entity that is colliding or nullptr if not colliding 
Dynamic* Dynamic::getCollidingFront(vector<Dynamic*>* vDynamic) {
	for (unsigned i = 0; i < vDynamic->size(); i++)
	{
		if (this != (*vDynamic)[i]) {
			float minDistance = Assets::get().GetSizeSprite() / 2;
			if(facingDirection == SOUTH){
				if (this->getPosX() + this->getWidth() > (*vDynamic)[i]->getPosX() && this->getPosX() < (*vDynamic)[i]->getPosX() + (*vDynamic)[i]->getWidth()) {
					float distanceY = (*vDynamic)[i]->getPosY() - (this->getPosY() + this->getWidth());
					if (distanceY < minDistance && distanceY > -minDistance) {
						return (*vDynamic)[i];
					}
				}
			}
			else if (facingDirection == NORTH) {
				if (this->getPosX() + this->getWidth() > (*vDynamic)[i]->getPosX() && this->getPosX() < (*vDynamic)[i]->getPosX() + (*vDynamic)[i]->getWidth()) {
					float distanceY = this->getPosY() - ((*vDynamic)[i]->getPosY() + (*vDynamic)[i]->getWidth());
					if (distanceY < minDistance && distanceY > -minDistance) {
						return (*vDynamic)[i];
					}
				}
			}
			else if (facingDirection == WEST) {
				float distanceX = this->getPosX() - ((*vDynamic)[i]->getPosX() + (*vDynamic)[i]->getWidth());
				if (distanceX < minDistance && distanceX > -minDistance) {
					if (this->getPosY() + this->getWidth() > (*vDynamic)[i]->getPosY() && this->getPosY() < (*vDynamic)[i]->getPosY() + (*vDynamic)[i]->getHeight()) {
						return (*vDynamic)[i];
					}
				}
			}
			else if (facingDirection == EAST) {
				float distanceX = (*vDynamic)[i]->getPosX() - (this->getPosX() + this->getWidth());
				if (distanceX < minDistance && distanceX > -minDistance) {
					if (this->getPosY() + this->getWidth() > (*vDynamic)[i]->getPosY() && this->getPosY() < (*vDynamic)[i]->getPosY() + (*vDynamic)[i]->getHeight()) {
						return (*vDynamic)[i];
					}
				}
			}
			// Old way: detects 360º interactions
			//if (this->getPosX() + this->getWidth() > (*vDynamic)[i]->getPosX() && this->getPosX() < (*vDynamic)[i]->getPosX() + (*vDynamic)[i]->getWidth()) {
			//	if (this->getPosY() + this->getWidth() > (*vDynamic)[i]->getPosY() && this->getPosY() < (*vDynamic)[i]->getPosY() + (*vDynamic)[i]->getHeight()) {
			//		//cout << this->getName() << " colliding with " << (*vDynamic)[i]->getName() << endl;

			//		return (*vDynamic)[i];
			//	}
			//}
		}
	}
	return nullptr;
}

// Return a boolean if it's colliding with a point
bool Dynamic::isCollidingDynamic(vector<Dynamic*>* vDynamic, float posX, float posY) {
	for (unsigned i =0; i < vDynamic->size(); i++)
	{
		if (this != (*vDynamic)[i] && (*vDynamic)[i]->getSolidVsDynamic()) {
			if (posX > (*vDynamic)[i]->getPosX() && posX < (*vDynamic)[i]->getPosX() + (*vDynamic)[i]->getWidth()) {
				if (posY > (*vDynamic)[i]->getPosY() && posY < (*vDynamic)[i]->getPosY() + (*vDynamic)[i]->getHeight()) {
					return true;
				}
			}
		}
	}
	return false;
}

// Return true if it's colliding with the player
bool Dynamic::isCollidingPlayer(Dynamic* pPlayer) {
	if (this->getPosX() + this->getWidth() > pPlayer->getPosX() && this->getPosX() < pPlayer->getPosX() + pPlayer->getWidth()) {
		if (this->getPosY() + this->getHeight() > pPlayer->getPosY() && this->getPosY() < pPlayer->getPosY() + pPlayer->getHeight()) {
			return true;
		}
	}
	return false;
}

// Return dynamic that's colliding with the player
Dynamic* Dynamic::getColliding(vector<Dynamic*> dynamics) {
	Dynamic* lastHit = nullptr;
	for (auto dynamic : dynamics) {
		if(this != dynamic && this->isFriendly() != dynamic->isFriendly())
		if (this->getPosX() + this->getWidth() > dynamic->getPosX() && this->getPosX() < dynamic->getPosX() + dynamic->getWidth()) {
			if (this->getPosY() + this->getHeight() > dynamic->getPosY() && this->getPosY() < dynamic->getPosY() + dynamic->getHeight()) {
				//return dynamic;
				lastHit = dynamic;
			}
		}
	}
	return lastHit;
	//return nullptr;
}



void Dynamic::applyFriction() {
	float friction = maxSpeed/20.f;
	float factorMaxSpeed = 1.f;
	if (vx != 0 && vy != 0)
		factorMaxSpeed = 0.71; // Simplification of a trigonometric limitation, to keep diagonal max speed = maxSpeed

	if (this->hasFriction) {
		// Horizontal
		if (abs(vx) < friction)
			vx = 0.f;
		if (vx > 0){
			vx -= friction;
			if (vx > this->maxSpeed * factorMaxSpeed)
				vx = this->maxSpeed * factorMaxSpeed;
		}else if (vx < 0) {
			vx += friction;
			if (vx < - this->maxSpeed * factorMaxSpeed)
				vx = -this->maxSpeed * factorMaxSpeed;
		}
		// Vertical
		if (abs(vy) < friction)
			vy = 0.f;
		if (vy > 0) {
			vy -= friction;
			if (vy > this->maxSpeed * factorMaxSpeed)
				vy = this->maxSpeed * factorMaxSpeed;
		}
		else if (vy < 0) {
			vy += friction;
			if (vy < -this->maxSpeed * factorMaxSpeed)
				vy = -this->maxSpeed * factorMaxSpeed;
		}
	}
}

// Inventory: Add
void Dynamic::addItem(Dynamic* itemToAdd) {
	for (unsigned i = 0; i < vInventory.size(); i++) {
		if (vInventory[i]->getName() == itemToAdd->getName() && ((cItem*)vInventory[i])->getStrength() == ((cItem*)itemToAdd)->getStrength()) { // If same type of item, and same strength
			((cItem*)vInventory[i])->updateQuantity(((cItem*)itemToAdd)->getQuantity()); // Adds to the existing item, the quantity of the incomming similar object
			return;
		}
	}
	// If not already in the inventory
	if (((cItem*)itemToAdd)->getQuantity() > 0) {
		this->vInventory.push_back(itemToAdd);
	}
}

// Inventory: Subtract, or remove the item if quantity 0 (quantity should be positive)
void Dynamic::consumeItem(string itemName, int quantity) {
	for (unsigned i = 0; i < vInventory.size(); i++) {
		if (((cItem*)vInventory[i])->getName() == itemName ) { // If same type of item
			if (((cItem*)vInventory[i])->isConsumable()) { // If is consumable
				if (quantity == 0 || !(((cItem*)vInventory[i])->updateQuantity(-quantity))) { // 0 to remove or Subtracts quantity
					vInventory.erase(vInventory.begin() + i); // Removes item from vector if quantity in item is less than zero
					// TODO: should delete here item?
					return;
				}
			}
			else if (dynamic_cast<cItem_Weapon *>(vInventory[i])) {
				this->setWeapon(vInventory[i]);
			}
		}
	}
}

bool Dynamic::hasItem(Dynamic* itemToCheck) {
	for (auto item : vInventory) {
		if (item->getName() == itemToCheck->getName()) {
			return true;
		}
	}
	return false;
}

// Return true if attacked
Dynamic* Dynamic::attackWeapon() {
	this->setAttacking(false); // After attack, reset boolean
	if (this->weapon != nullptr) {
		cProjectile* projectile = ((cItem_Weapon*)this->weapon)->OnWeaponUse(this); 
		if (projectile != nullptr) {
			return projectile;
		}
	}
	else {
		return nullptr;
	}
}