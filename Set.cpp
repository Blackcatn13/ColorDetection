#include "Set.h"

// Default Constructor of the class
Set::Set(){
  Points = vector<DPoint*>();
}
// Function to add a Point to the set
void Set::addPoint(DPoint *p){
  Points.push_back(p);
}

// Function to compare to DPoint pointers
bool compare(DPoint *p1, DPoint *p2){
    return *p1 < *p2;
}

// Funtion to return equality between to DPoint pointers
bool same(DPoint *p1, DPoint *p2){
    return *p1 == *p2;
}

// Funtion that returns k random pointss
vector<DPoint*> Set::getRandomPoints(int k){
  list<DPoint*> removequals = list<DPoint*>(Points.begin(), Points.end());
  removequals.sort(compare);
  removequals.unique(same);
  vector<DPoint*> vecaux = vector<DPoint*>(removequals.begin(), removequals.end());
  random_shuffle(vecaux.begin(), vecaux.end());
  vecaux.resize(k);
  return vecaux;
}

