#include "Set.h"

// Default Constructor of the class
Set::Set(){
  Points = vector<DPoint>();
}
// Function to add a Point to the set
void Set::addPoint(DPoint p){
  Points.push_back(p);
}
// Funtion that returns k random pointss
vector<DPoint> Set::getRandomPoints(int k){
  list<DPoint> removequals = list<DPoint>(Points.begin(), Points.end());
  removequals.sort();
  removequals.unique();
  vector<DPoint> vecaux = vector<DPoint>(removequals.begin(), removequals.end());
  random_shuffle(vecaux.begin(), vecaux.end());
  vecaux.resize(k);
  return vecaux;
}