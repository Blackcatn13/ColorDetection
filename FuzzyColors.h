#ifndef FuzzyColors_H
#define FuzzyColors_H

#include <vector>
#include "DPoint.h"
#include "Set.h"
#include <fstream>
#include <sstream>

#include <iostream>

vector<int> getFuzzyCIELAB(vector<DPoint*> points);
vector<int> getFuzzyRGB(vector<DPoint*> points, vector<Set>);

#endif
