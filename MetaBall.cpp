#include "MetaBall.h"
#include "modelerview.h"
MetaBall::MetaBall(int x, int y, int z, float r, float L, char* label) :Component(METABALL) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->radius = r;
	this->thetax = 0;
	xoffset = 0;
	yoffset = 0;
	zoffset = 0;
	thetax = 0;
	thetay = 0;
	thetaz = 0;
	thetaxOff = 0;
	thetayOff = 0;
	thetazOff = 0;
}