#ifndef Kmeans_H
#define Kmeans_H

#include "DPoint.h"
#include <vector>
#include "Set.h"
#include <algorithm>

using namespace std;
// Class that represent the calculation of the algorithm K-Means for a DPoint and a Set of DPoints
class Kmeans{
  vector<DPoint> InertiaCenter;
  vector<DPoint> OldInertiaCenter;
  vector<DPoint> Points;
  Set InitialSet;
  int k;
  vector<Set> Class;
public:
  Kmeans(Set s);
  Kmeans();
  vector<Set> Calculate(int k);
private:
  int PosMinDistance(DPoint point);
  vector<DPoint> getNewInertiaCenters();
  DPoint getNewInertiaCenter(vector<DPoint> points);
  void ClearClass(int k);
};

#endif