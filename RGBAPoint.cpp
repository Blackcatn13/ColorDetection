#include "RGBAPoint.h"

RGBAPoint::RGBAPoint(){
}

// Function to get the distance between two RGB points
float RGBAPoint::Distance(DPoint *p){
  float dist = 0;
  for(int i = 0; i < p->getDimension(); i++){
    dist += pow((double)(Position[i] - p->getPosition()[i]), 2);
  }
  dist = sqrt(dist); 
  return dist;
}