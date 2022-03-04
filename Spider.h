#pragma once
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include "UpperLeg.h"
#include <FL/gl.h>

#include "modelerglobals.h"

struct Spider
{
    Spider(int x, int y,int z, int w,int l,int h, ModelerView* view);
    ModelerView* view;
    //body parts
    int w;
    int h;
    int l;
    int x;
    int y;
    int z;
    int thetax;
    int thetay;
    int thetaz;

    UpperLeg* ulu_Leg;
    UpperLeg* uld_Leg;
    UpperLeg* uru_Leg;
    UpperLeg* urd_Leg;



    virtual void draw();
};