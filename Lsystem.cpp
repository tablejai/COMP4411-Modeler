#include "Lsystem.h"
using namespace std;
Lsystem::Lsystem(int x, int y, int z, int depth) :Component(UPPERLEG) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->thetax = 0;
	db = new DragonBranch(0, 0, 0, depth);
	kc = new KochBranch(0, 0, 0, depth);
	fc = new Fractal(0, 0, 0, depth);
	xoffset = 0;//for debug mainly
	yoffset = 0;
	zoffset = 0;
	thetax = 0;
	thetay = 0;
	thetaz = 0;
	thetaxOff = 0;
	thetayOff = 0;
	thetazOff = 0;
}
void Lsystem::draw()
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
	glPushMatrix();
	if (VAL(LSYSTEMOBJECTTYPE) == Dragon) {
		db->length = VAL(LSYSTEMDVALUE);
		db->depth = depth;
		db->setCode();
		db->draw();
	}
	else if (VAL(LSYSTEMOBJECTTYPE) == KochCurve) {
		kc->length = VAL(LSYSTEMDVALUE);
		kc->depth = depth;
		kc->setCode();
		kc->draw();
	}
	else if (VAL(LSYSTEMOBJECTTYPE) == FractalTree) {
		fc->length = VAL(LSYSTEMDVALUE);
		fc->depth = depth;
		fc->setCode();
		fc->draw();
	}
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

}
