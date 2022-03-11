#include "Head.h"
using namespace std;
 Head:: Head(int x, int y, int z, float w, float L, float H, char* label) :Component(HEAD) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->width = w;
	this->length = L;
	this->thetax = 0;
	this->height = H;
	for (int i = 0;i < 2;i++) {
		MetaBall* ptr = new MetaBall(0, 0, i * 2 + 0.4, 1.0f, nullptr);
		metaballs.push_back(ptr);
	}
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

void drawRect(float length, float width,float height) {
	 
}


void drawFace(vector<vector<double>> points) {
	vector<double> pt1 = points[0];

	vector<double> pt2 = points[1];
#define mid(a,b) (a+b)/2.0
	vector<double> mid = { mid(pt1[0],pt2[0]),mid(pt1[1],pt2[1]),mid(pt1[2],pt2[2])};
	for (int i = 0;i < points.size();i++) {
		vector<double> next;
		if (i + 1 >= points.size()) {
			next = points[0];
		}
		else {
			next = points[i + 1];
		}
		vector<double> pt = points[i];
		drawTriangle(pt[0], pt[1], pt[2], mid[0], mid[1], mid[2], next[0], next[1], next[2]);
	}
	

}
void  Head::draw()
{
	// This call takes care of a lot of the nasty projection 
	// matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
	// draw the leg
#define HEIGHT_HALF height/2
#define WIDTH_HALF width/2
#define LENGTH_HALF length/2

	vector<vector<double>>Faces[8];
	//int counRect=0;
	for (int i = 0;i < 6;i++) {
		Faces[0].push_back(vector<double>{ width*cos(i*M_PI/3.0), HEIGHT_HALF, width* sin(i* M_PI / 3.0) });
		Faces[1].push_back(vector<double>{ width* cos(i* M_PI / 3.0), -HEIGHT_HALF, width* sin(i* M_PI / 3.0) });
		if (i > 0) {
				Faces[1 + i].push_back(vector<double>{ Faces[0][i - 1][0], -HEIGHT_HALF, Faces[0][i - 1][2] });
				Faces[1 + i].push_back(vector<double>{ Faces[0][i - 1][0], HEIGHT_HALF, Faces[0][i - 1][2] });
				Faces[1 + i].push_back(vector<double>{ Faces[0][i][0], HEIGHT_HALF, Faces[0][i][2] });
				Faces[1+ i].push_back(vector<double>{ Faces[0][i][0], -HEIGHT_HALF, Faces[0][i][2] });
		}
	}
	

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



	for (int i = 0;i <8;i++) {
		if (Faces[i].size() >= 2)
			drawFace(Faces[i]);
	}



	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

}
