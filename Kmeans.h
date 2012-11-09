#ifndef Kmeans_H
#define Kmeans_H

#include "DPoint.h"
#include <vector>
#include "Set.h"
#include <algorithm>
#include <iostream>
#include <time.h>

using namespace std;
// Class that represent the calculation of the algorithm K-Means for a DPoint and a Set of DPoints
class Kmeans{
  vector<DPoint*> InertiaCenter;
  vector<DPoint*> OldInertiaCenter;
  vector<DPoint*> Points;
  Set InitialSet;
  int k;
  vector<Set> Class;
public:
  Kmeans(Set s);
  Kmeans();
  vector<Set> Calculate(int k, bool verbose);
  vector<DPoint*> getInertiaCenter() {return InertiaCenter;}
private:
  int PosMinDistance(DPoint *point);
  vector<DPoint*> getNewInertiaCenters();
  DPoint* getNewInertiaCenter(vector<DPoint*> points);
  void ClearClass(int k);
  void Printime(double Time);
  bool equals(vector<DPoint*> v1, vector<DPoint*> v2);
};

#endif