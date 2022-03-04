#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>

#include "modelerglobals.h"

struct Head : public ModelerView
{
    Head(int x, int y, int w, int h, char* label)
        : ModelerView(x, y, w, h, label) { }

    virtual void draw();
};