#ifndef FuzzyColors_H
#define FuzzyColors_H

#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "DPoint.h"
#include "CIELABPoint.h"
#include "RGBAPoint.h"
#include "Set.h"

vector<int> getFuzzyCIELAB(vector<DPoint*> points);
vector<int> getFuzzyRGB(vector<DPoint*> points, vector<Set> globalSet);

#endif
