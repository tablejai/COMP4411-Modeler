#include "DragonBranch.h"
#include <iostream>
using namespace std;
DragonBranch::DragonBranch(int x, int y, int z, int depth ) :Component(UPPERLEG){
	this->x = x;
	this->y = y;
	this->z = z;
	this->thetax = 0;
	xoffset = 0;//for debug mainly
	yoffset = 0;
	zoffset = 0;
	this->depth = depth;
	code = "F";
	setCode();
	thetax = 0;
	thetay = 0;
	thetaz = 0;
	thetaxOff = 0;
	thetayOff = 0;
	thetazOff = 0;
}
void DragonBranch::setCode() {
	code = "F";
	for (int i = 0;i < depth;i++) {
		string temp = "";

		for (int j = 0;j < code.size();j++) {
			if (code[j] == 'F') {
				temp += "F+G";
			}
			else if (code[j] == 'G') {
				temp += "F-G";
			}
			else if (code[j] == '+') {
				temp += '+';
			}
			else {
				temp += '-';
			}
		}
		code = temp;
	}
}

void DragonBranch::draw()
{
	// This call takes care of a lot of the nasty projection 
	// matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
	// draw the leg
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_RED);
	glPushMatrix();
	glTranslated(x + xoffset, y + yoffset, z + zoffset);
	glPushMatrix();
	glRotatef(thetax + thetaxOff, 1, 0, 0);
	glPushMatrix();
	glRotatef(thetay + thetayOff, 0, 1, 0);
	glPushMatrix();
	glRotatef(thetaz + thetazOff, 0, 0, 1);
	for (int i = 0;i < code.size();i++) {
		
		if (code[i] == 'F' || code[i]=='G'){
			glBegin(GL_LINES);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, length);
			glEnd();
			glPushMatrix();
			glTranslated(0,0,length);
		}
		else if (code[i] =='+') {
			glPushMatrix();
			glRotatef(90, 0,1,0);
		}
		else if (code[i] == '-') {
			glPushMatrix();
			glRotatef(270, 0, 1, 0);
		}
	}
	for (int i = 0;i < code.size();i++) {
		glPopMatrix();
	}
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


}

DragonBranch::~DragonBranch() {
	
}
