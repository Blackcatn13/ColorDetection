#include "DPoint.h"

// Default constructor of the class
DPoint::DPoint(){
  Position = vector<float>();
}
// Function to set a new position to the point
void DPoint::setPosition(vector<float> nposition){
  Position = nposition;
}
// Function that returns the distance between this point and the parameter point
float DPoint::Distance(DPoint p){
  float dist = 0;
  for(int i = 0; i < p.getDimension(); i++){
    dist += pow((double)(Position[i] - p.getPosition()[i]), 2);
  }
  dist = sqrt(dist);
  return dist;
}
// Override of the operator equals
bool DPoint::operator==(const DPoint &p){
  return (Position == p.Position);
}
// Override of the operator not equals
bool DPoint::operator!=(const DPoint &p){
  return (Position != p.Position);
}
//Override of the operator minor
bool DPoint::operator<(const DPoint &p){
  float mod1;
  float mod2;
  float dist1 = 0;
  float dist2 = 0;
  for(int i = 0; i < getDimension(); i++){
    dist1 += pow((double)Position[i], 2);
    dist2 += pow((double)p.Position[i], 2);
  }
  mod1 = sqrt(dist1);
  mod2 = sqrt(dist2);
  return mod1 < mod2;
}