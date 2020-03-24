#include "item.h"
#include "assets.h"

cItem::cItem(string name, string asset, string desc, int usesRemainning) {
	this->sName = name;
	this->sAsset = asset;
	this->sDesc = desc;
	this->iUsesRemainning = usesRemainning;
}