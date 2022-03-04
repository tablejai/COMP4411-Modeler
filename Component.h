#pragma once
typedef enum {
	UPPERLEG,
	LOWERLEG,
	HAND,
	NUMTYPE
}Type;
struct Component {
	Type  type;
	Component(Type t):type(t){

	}
	//virtual void draw();
};