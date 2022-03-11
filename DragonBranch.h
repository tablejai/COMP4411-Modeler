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

struct DragonBranch : public Component
{
    float length = 0.5;
    
     string code;
    DragonBranch(int x, int y, int z, int depth);
    virtual void draw();
    ~DragonBranch();
    void  setCode();
    int depth = 0;

};