#include "Tentacle.h"

#define M_PI 3.141592653589793238462643383279502

Tentacle::Tentacle(Tentacle* _parent, XYZ _start, float r, float l) {
	parent = _parent;
	start = _start;
	radius = r;
	length = l;

	follow(XYZ{VAL(TENTACLE_X_TAR), VAL(TENTACLE_Y_TAR), VAL(TENTACLE_Z_TAR)});
	update();
}

static void cross(Vec3f vec1, Vec3f vec2, Vec3f& crossProduct)
{
	crossProduct[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
	crossProduct[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
	crossProduct[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
}

static float dot(Vec3f vec1, Vec3f vec2) {
	return vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2];
}

void Tentacle::drawCylinderWithTwoPts(XYZ a, XYZ b) {
	Vec3f z = { 0,0,1 };
	Vec3f p = {(float)(a.x - b.x), (float)(a.y - b.y), (float)(a.z - b.z) };
	Vec3f t;
	cross(z, p, t);

	double angle = 180 / M_PI * acos(dot(z,p)/p.length());
	
	glPushMatrix();
	glTranslated(start.x, start.y, start.z);
	glPushMatrix();
	glRotated(angle, t[0], t[1], t[2]);
	glPushMatrix();


	GLUquadric* quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricOrientation(quadric, GLU_OUTSIDE);
	gluCylinder(quadric ,radius, radius, p.length(), 50, 50);

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

}

Tentacle::Tentacle(XYZ _start, float r, float l) {
	start = _start;
	radius = r;
	length = l;

	follow(XYZ{VAL(TENTACLE_X_TAR), VAL(TENTACLE_Y_TAR), VAL(TENTACLE_Z_TAR)});
	update();
}

void Tentacle::followParent() {
	follow(XYZ(parent->start));
}

void Tentacle::follow(XYZ tar) {
	XYZ dir = XYZ{ tar.x - start.x, tar.y - start.y, tar.z - start.z };
	// TODO: Check the angles
	float magnitude = sqrtf(dir.x* dir.x+ dir.y * dir.y + dir.z * dir.z);
	theta[0] = atan2(dir.y, dir.x);
	theta[1] = asin(dir.z / magnitude);
	//theta[1] = atan2(dir.z, dir.x);
	

	//float magnitude = sqrtf(dir.x* dir.x+ dir.y * dir.y + dir.z * dir.z);
	//dir.x = dir.x * length / magnitude * -1.0;
	//dir.y = dir.y * length / magnitude * -1.0;
	//dir.z = dir.z * length / magnitude * -1.0;

	//start = { tar.x + dir.x, tar.y + dir.y, tar.z + dir.z };
};

void Tentacle::draw() {
	setAmbientColor(.3f, .3f, .3f);
	setDiffuseColor(COLOR_BLUE);
	drawCylinderWithTwoPts(start, end);
}

void Tentacle::update() {
	// TODO: Check the angles
	float dx = length * cos(theta[0]);
	float dy = length * sin(theta[0]);
	float dz = length * sin(theta[1]);
	end = XYZ{ start.x + dx, start.y + dy, start.z + dz };
}