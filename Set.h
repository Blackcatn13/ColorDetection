#ifndef Set_H
#define Set_H

#include "DPoint.h"
#include <vector>
#include <algorithm>
#include <list>

using namespace std;
// Class that represents a set of DPoints
class Set{
  vector<DPoint*> Points;
public:
  Set();
  vector<DPoint*> getPoints() {return Points;}
  void addPoint(DPoint *p);
  virtual vector<DPoint*> getRandomPoints(int k);
};

#endif