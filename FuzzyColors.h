#ifndef FuzzyColors_H
#define FuzzyColors_H

#include <vector>
#include "DPoint.h"

vector<int> getFuzzyCIELAB(vector<DPoint*> points);
vector<int> getFuzzyRGB(vector<DPoint*> points);

#endif