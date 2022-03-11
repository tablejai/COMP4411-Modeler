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

#include <string>
using namespace std;

struct KochBranch : public Component
{
    float length;

    string code;
    KochBranch(int x, int y, int z, int depth);
    virtual void draw();
    void  setCode();
    int depth = 0;

};