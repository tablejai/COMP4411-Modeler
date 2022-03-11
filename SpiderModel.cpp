#include "SpiderModel.h"
SpiderModel:: SpiderModel(int x, int y, int w, int h, char* label): ModelerView(x, y, w, h, label) {
	spider = new Spider(0, 0,0, 4, 2, 2, this);
	lsystem = new Lsystem(0,0,0,VAL(LSYSTEMITER));
}
void SpiderModel::draw()
{
	// This call takes care of a lot of the nasty projection 
	// matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
	ModelerView::draw();
	if (VAL(LSYSTEMDISPLAY) == 0)
		spider->draw();
	else {
		lsystem->depth = VAL(LSYSTEMITER);
		lsystem->draw();
	}
	// draw the floor
	
}
