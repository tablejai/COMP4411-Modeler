#ifndef _MODELER_GLOBALS_H
#define _MODELER_GLOBALS_H

#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502
#endif

// This is a list of the controls for the SampleModel
// We'll use these constants to access the values 
// of the controls from the user interface.
enum SampleModelControls
{ 
	LEVEL_OF_DETAIL, XPOS, YPOS, ZPOS, XTHETA,YTHETA, ZTHETA, OSCILLATEY, HEIGHT, ROTATE, RESOLUTIONMETABALL, LSYSTEMDISPLAY,LSYSTEMOBJECTTYPE,
	LSYSTEMDVALUE,
	LSYSTEMINITIALANGLE,
	FRAME, CHANGE_LEG, CHANGE_HEAD, CHANGE_BODY,
	LSYSTEMITER, MOVECANON, ANIMATE, HIGHNESS,TENTACLE_X_TAR, TENTACLE_Y_TAR, TENTACLE_Z_TAR, TENTACLE_ANG_CONSTRAINT, NUMCONTROLS

};

// Colors
#define COLOR_RED		1.0f, 0.0f, 0.0f
#define COLOR_GREEN		0.0f, 1.0f, 0.0f
#define COLOR_BLUE		0.0f, 0.0f, 1.0f

// We'll be getting the instance of the application a lot; 
// might as well have it as a macro.
#define VAL(x) (ModelerApplication::Instance()->GetControlValue(x))

#endif