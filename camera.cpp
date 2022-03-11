#include <windows.h>
#include <Fl/gl.h>
#include <gl/glu.h>

#include "camera.h"
#include "modelerglobals.h" 
#include "modelerapp.h"
#include <vector>
using namespace std;

#pragma warning(push)
#pragma warning(disable : 4244)

#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502
#endif 

const float kMouseRotationSensitivity		= 1.0f/90.0f;
const float kMouseTranslationXSensitivity	= 0.03f;
const float kMouseTranslationYSensitivity	= 0.03f;
const float kMouseZoomSensitivity			= 0.08f;
const float kMouseTwistSensitivity			= 0.08f;

void MakeDiagonal(Mat4f &m, float k)
{
	register int i,j;

	for (i=0; i<4; i++)
		for (j=0; j<4; j++)
			m[i][j] = (i==j) ? k : 0.0f;
}

void MakeHScale(Mat4f &m, const Vec3f &s)	
{
	MakeDiagonal(m,1.0f);
	m[0][0] = s[0]; m[1][1] = s[1];	m[2][2] = s[2];
}

void MakeHTrans(Mat4f &m, const Vec3f &s)
{
	MakeDiagonal(m,1.0f);
	m[0][3] = s[0]; m[1][3] = s[1]; m[2][3] = s[2];
}

void MakeHRotX(Mat4f &m, float theta)
{
	MakeDiagonal(m,1.0f);
	float cosTheta = cos(theta);
	float sinTheta = sin(theta);
	m[1][1] = cosTheta;
	m[1][2] = -sinTheta;
	m[2][1] = sinTheta;
	m[2][2] = cosTheta;
}

void MakeHRotY(Mat4f &m, float theta)
{
	MakeDiagonal(m,1.0f);
	float cosTheta = cos(theta);
	float sinTheta = sin(theta);
	m[0][0] = cosTheta;
	m[2][0] = -sinTheta;
	m[0][2] = sinTheta;
	m[2][2] = cosTheta;
}

void MakeHRotZ(Mat4f &m, float theta)
{
	MakeDiagonal(m,1.0f);
	float cosTheta = cos(theta);
	float sinTheta = sin(theta);
	m[0][0] = cosTheta;
	m[0][1] = -sinTheta;
	m[1][0] = sinTheta;
	m[1][1] = cosTheta;
}


void Camera::calculateViewingTransformParameters() 
{
	Mat4f dollyXform;
	Mat4f azimXform;
	Mat4f elevXform;
	Mat4f twistXform;
	Mat4f originXform;

	Vec3f upVector;

	MakeHTrans(dollyXform, Vec3f(0,0,mDolly));
	MakeHRotY(azimXform, mAzimuth);
	MakeHRotX(elevXform, mElevation);
	MakeDiagonal(twistXform, 1.0f);
	MakeHTrans(originXform, mLookAt);
	
	mPosition = Vec3f(0,0,0);
	// grouped for (mat4 * vec3) ops instead of (mat4 * mat4) ops
	//if (VAL(LSYSTEMDISPLAY) == 0) {
	mPosition = originXform * (azimXform * (elevXform * (dollyXform * mPosition)));

	if ( fmod((double)mElevation, 2.0*M_PI) < 3*M_PI/2 && fmod((double)mElevation, 2.0*M_PI) > M_PI/2 )
		mUpVector= Vec3f(sin(mTwist), -cos(mTwist),0);
	else
		mUpVector= Vec3f(sin(mTwist),cos(mTwist),0);

	mDirtyTransform = false;
}

Camera::Camera() 
{
	mElevation = mAzimuth = mTwist = 0.0f;
	mTwist = -M_PI;
	mDolly = -20.0f;
	mElevation = 0.2f;
	mAzimuth = (float)M_PI;

	mLookAt = Vec3f( 0, 0, 0 );
	mCurrentMouseAction = kActionNone;

	calculateViewingTransformParameters();
}

void Camera::clickMouse( MouseAction_t action, int x, int y )
{
	mCurrentMouseAction = action;
	mLastMousePosition[0] = x;
	mLastMousePosition[1] = y;
}

void Camera::dragMouse( int x, int y )
{
	Vec3f mouseDelta   = Vec3f(x,y,0.0f) - mLastMousePosition;
	mLastMousePosition = Vec3f(x,y,0.0f);
	switch(mCurrentMouseAction)
	{
	case kActionTranslate:
		{
			calculateViewingTransformParameters();

			double xTrack =  -mouseDelta[0] * kMouseTranslationXSensitivity;
			double yTrack =  mouseDelta[1] * kMouseTranslationYSensitivity;

			Vec3f transXAxis;
			
	        transXAxis = mUpVector ^ (mPosition - mLookAt);

			transXAxis /= sqrt((transXAxis*transXAxis));
		
			Vec3f transYAxis = (mPosition - mLookAt) ^ transXAxis;
			transYAxis /= sqrt((transYAxis*transYAxis));

			setLookAt(getLookAt() + transXAxis*xTrack + transYAxis*yTrack);
			
			break;
		}
	case kActionRotate:
		{
			float dAzimuth		=   -mouseDelta[0] * kMouseRotationSensitivity;
			float dElevation	=   mouseDelta[1] * kMouseRotationSensitivity;
			
			setAzimuth(getAzimuth() + dAzimuth);
			setElevation(getElevation() + dElevation);
			
			break;
		}
	case kActionZoom:
		{
			float dDolly = -mouseDelta[1] * kMouseZoomSensitivity;
			setDolly(getDolly() + dDolly);
			break;
		}
	case kActionTwist:
		{
		float twist = -mouseDelta[0] * kMouseTwistSensitivity;
		setTwist(getTwist() + twist);
			break;
		}
		// Not implemented
	default:
		break;
	}

}

void Camera::releaseMouse( int x, int y )
{
	mCurrentMouseAction = kActionNone;
}
void cross(Vec3f vec1, Vec3f vec2, Vec3f& crossProduct)

{

	crossProduct[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
	crossProduct[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
	crossProduct[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
}
void norm(Vec3f& vec1) {
	float mag = sqrt(vec1[0] * vec1[0] + vec1[1] * vec1[1] + vec1[2] * vec1[2]);
	for (int i = 0;i < 3;i++) {
		vec1[i] /= mag;
	}
}
void Camera::lookAt(Vec3f eye, Vec3f at, Vec3f up)
{
	Vec3f forward, side, upVec;
	float m[16], resultMatrix[16];

	forward[0] = at[0] - eye[0];
	forward[1] = at[1] - eye[1];
	forward[2] = at[2] - eye[2];
	
	norm(forward);
	cross(up, forward,side);
	norm(side);
	cross(side, forward, upVec);
	m[0] = side[0];
	m[4] = side[1];
	m[8] = side[2];
	m[12] = 0.0;
	m[1] = upVec[0];
	m[5] = upVec[1];
	m[9] = upVec[2];
	m[13] = 0.0;
	m[2] = -forward[0];
	m[6] = -forward[1];
	m[10] = -forward[2];
	m[14] = 0.0;
	m[3] = m[7] = m[11] = 0.0;
	m[15] = 1.0;
	glMultMatrixf(m);
	glTranslated(-eye[0], -eye[1], -eye[2]);
}
 void Camera::frameAllView(float xchange, float ychange, float zchange)
{

	mPosition = Vec3f(1.91546f*2 + xchange, 22.1527*2 + ychange, 0.343346*2 + zchange);
	mLookAt = Vec3f(-1.26334 + xchange, 2.4072 + ychange, 0.436215 + zchange);
	mUpVector = Vec3f(0.0f, 1.0f, 0.0f);
	lookAt(mPosition, mLookAt, mUpVector);
}
void Camera::applyViewingTransform() {
	if( mDirtyTransform )
		calculateViewingTransformParameters();

	// Place the camera at mPosition, aim the camera at
	// mLookAt, and twist the camera such that mUpVector is up
	/*gluLookAt(	mPosition[0], mPosition[1], mPosition[2],
				mLookAt[0],   mLookAt[1],   mLookAt[2],
				mUpVector[0], mUpVector[1], mUpVector[2]);*/
	//float* eye = new float[3]{ mPosition[0],mPosition[1],mPosition[2] };
	//float* center = new float[3]{ mLookAt[0],   mLookAt[1],   mLookAt[2] };
	//float* up=new float[3]{ mUpVector[0],mUpVector[1],mUpVector[2] };
	if(VAL(FRAME)==1)
	 frameAllView(VAL(XPOS), VAL(YPOS), VAL(ZPOS));
	else
	  lookAt(mPosition, mLookAt, mUpVector);
	for (int i = 0;i < 3;i++) {
		cout<<"pos: " << mPosition[i] << endl;
	}
	cout << "xxxxxxxxxxx" << endl;
	for (int i = 0;i < 3;i++) {
		cout<<"lookAt: "  << mLookAt[i] << endl;
	}
}


#pragma warning(pop)