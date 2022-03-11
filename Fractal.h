#pragma once
#pragma once
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
#include <vector>
#include <algorithm>
#include <stack>
#include <string>
using namespace std;
typedef struct {
    float x;
    float y;
    float z;
} Point3D;
struct Fractal : public Component
{
     float length;

    string code;
    Fractal(int x, int y, int z, int depth);
    virtual void draw();
    stack<Point3D> stk;
    void  setCode();
    int depth = 0;
    void Fractal::drawline();
    void Fractal::drawleave();
    void forwardAndRotateL();
    void forwardAndRotateR();

};