#ifndef InitVectorsFunctions_H
#define InitVectorsFunctions_H

#include "DPoint.h"
#include <vector>

// Functions to init the 11 colors to compare
vector<DPoint*> initDefault();
vector<DPoint*> initRGB();
vector<DPoint*> initDefactoCIELAB();
vector<DPoint*> initCIELAB();
vector<DPoint*> initHSV();

#endif