#include "Fractal.h"
#include <iostream>
using namespace std;
Fractal::Fractal(int x, int y, int z, int depth) :Component(UPPERLEG) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->thetax = 0;
	xoffset = 0;//for debug mainly
	yoffset = 0;
	zoffset = 0;
	this->depth = depth;
	code = "0";
	setCode();
	thetax = 0;
	thetay = 0;
	thetaz = 0;
	thetaxOff = 0;
	thetayOff = 0;
	thetazOff = 0;
}
void Fractal::setCode() {
	code = "0";
	for (int i = 0;i < depth;i++) {
		string temp = "";
		for (int j = 0;j < code.size();j++) {
			if (code[j] == '1') {
				temp += "11";
			}
			else if (code[j] == '0') {
				temp += "1[0]0";
			}
			else if (code[j] == ']') {
				temp += "]";
			}
			else {
				temp += "[";
			}
		}
		code = temp;
	}
	cout << code << endl;
}

void Fractal::drawline() {
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, length);
	glEnd();
	glTranslated(0, 0, length);

}
void Fractal::drawleave() {
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, length);
	glEnd();

}
void Fractal::forwardAndRotateL() {
	glRotatef(-45, 0, 1, 0);
}
void Fractal::forwardAndRotateR() {
//	glTranslated(0, 0, length);
	glRotatef(45, 0, 1, 0);
}

void Fractal::draw()
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

	int count = 0;
	for (int i = 0;i < code.size();i++) {

		if (code[i] == '1') {
			drawline();
		}
		else if (code[i] == '0') {
			drawleave();
		
		}
		else if (code[i] == '[') {
			glPushMatrix();
			forwardAndRotateL();
		}
		else if (code[i] == ']') {
			glPopMatrix();
			forwardAndRotateR();
		}
	}
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


}

