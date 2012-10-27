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
  vector<DPoint> auxp = Points;
  random_shuffle(auxp.begin(), auxp.end());
  auxp.resize(k);
  return auxp;
}