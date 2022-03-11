#include "Spider.h"
#include "bitmap.h"

void Spider::loadTextureShield(char* fName) {
	int textureWidth, textureHeight;
	unsigned char* image = readBMP(fName, textureWidth, textureHeight);

	GLuint textureObj;

	glGenTextures(1, &textureObj);
	glBindTexture(GL_TEXTURE_2D, textureObj);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);	

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);

	glNormal3d(0, 0, -1.0);
	glTexCoord2f(0.0, 1.0); glVertex3d(-1.0, -1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3d(-1.0, -1.0, 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3d(0.0, -1.0, 0.0);
	glTexCoord2f(1.0, 1.0); glVertex3d(0.0, -1.0, 1.0);


	glEnd();
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}
Spider::Spider(int x, int y, int z,int w, int h, int L, ModelerView * view) {
	float lg_xoffset = 0.82;
	float lg_zoffset = 0.88;

	 ulu_Leg = new UpperLeg(w+x- lg_xoffset,y , z+ L- lg_zoffset, 0.2,3 , nullptr);
	 ulu_Leg->thetax = 20;
	 ulu_Leg->lowerleg->thetax = 69.15;
	 uld_Leg = new UpperLeg(w+x- lg_xoffset, y, z-L+ lg_zoffset, 0.2, 3, nullptr);
	 uld_Leg->thetax = 160;
	 uld_Leg->lowerleg->thetax = -69.15+360;

	 uru_Leg = new UpperLeg(-w+x + lg_xoffset, y, z + L- lg_zoffset, 0.2, 3, nullptr);
	 uru_Leg->thetax = 20;
	 uru_Leg->lowerleg->thetax = 69.15;

	 urd_Leg = new UpperLeg(-w+ x + lg_xoffset, y, z - L+ lg_zoffset, 0.2, 3, nullptr);
	 urd_Leg->thetax = 160;
	 urd_Leg->lowerleg->thetax = -69.15 + 360;
	// metaball = new MetaBall(x, y, z,1,nullptr);
	 canon = new Canon(x, y+ 1.0, z+2.23, 0.3, 7, nullptr);
	 canon->thetax = 270;
	 canon->thetay = 270;

	 this->view = view;
	 this->x = x;
	 this->y = y;
	 this->z = z;
	 this->w = w;
	 this->h = h;
	 this->l = L;
 }

void Spider::draw()
{
	// This call takes care of a lot of the nasty projection 
	// matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
	// draw the body
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_GREEN);
	glPushMatrix();
	//glTranslated(VAL(XPOS), VAL(YPOS),VAL(ZPOS));
	glPushMatrix();
	//glTranslated(-w/2.0, -h/2.0, -l/2.0);
	glScaled(w, h,l );
	drawSphere(1);
	loadTextureShield("meme.bmp");

	glPopMatrix();
	//TestComp(ulu_Leg);
	OscillateCompY(ulu_Leg,10);
	OscillateCompY(uld_Leg, -10);
	OscillateCompY(uru_Leg, 10);
	OscillateCompY(urd_Leg, -10);

	ulu_Leg->draw();
	uld_Leg->draw();
	uru_Leg->draw();
	urd_Leg->draw();
	//TestComp(canon);
	canon->draw();
	glPopMatrix();
}
