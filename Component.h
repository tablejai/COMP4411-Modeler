#pragma once
typedef enum {
	UPPERLEG,
	LOWERLEG,
	HAND,
	HEAD,
	METABALL,
	NUMTYPE
}Type;
struct Component {
	Type  type;
	float x;
	float y;
	float z;
	float xoffset;//for debug mainly
	float yoffset;
	float zoffset;
	float thetax;
	float thetay;
	float thetaz;
	float thetaxOff;
	float thetayOff;
	float thetazOff;
	Component(Type t):type(t){

	}
	//virtual void draw();
};