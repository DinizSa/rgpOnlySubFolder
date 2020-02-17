#include "interactive.h"

Interactive::Interactive():
	Dynamic() {

}
Interactive::Interactive(string name, float px, float py, float width, float height) :
	Dynamic(name, px, py, 0.f, 0.f, width, height, true, true, true, true, 0) {

}

Interactive::~Interactive() {

}