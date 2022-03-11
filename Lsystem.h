#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>
#include "modelerglobals.h"
#include "Joint.h"
#include "LowerLeg.h"
#include "Component.h"
#include "MetaBall.h"
#include "global.h"
#include "DragonBranch.h"
#include "KochCurve.h"
#include "Fractal.h"
#include <vector>
#include <algorithm>
typedef enum {
    FractalTree,
    KochCurve,
    Dragon
}LTYPE;
struct Lsystem : public Component
{
    Lsystem(int x, int y, int z,int depth);
    int depth = 0;
    DragonBranch* db;
    KochBranch* kc;
    Fractal* fc;
    virtual void draw();
};