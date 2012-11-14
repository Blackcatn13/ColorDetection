#include "HSVPoint.h"

HSVPoint::HSVPoint(){
}

float HSVPoint::Distance(DPoint *p){
  float dist = -1;
  float hue, sat, val, hue1, sat1, val1;
  float huedist, satdist, valdist;
  // HSVPoint: (hue, saturation, value)
  // (v*s*cos(2*PI*h) - v'*s'*cos(2*PI*h'),v*s*sin(2*PI*h) - v'*s'*sin(2*PI*h'), v-v')

  hue = Position[0];
  sat = Position[1];
  val = Position[2];
  hue1 = p->getPosition()[0];
  sat1 = p->getPosition()[1];
  val1 = p->getPosition()[2];
  huedist = (val *sat*cos(2*PI*hue)) - (val1*sat1*cos(2*PI*hue1));
  satdist = (val *sat*sin(2*PI*hue)) - (val1*sat1*sin(2*PI*hue1));
  valdist = val - val1;
  dist = sqrt(pow(huedist,2)+pow(satdist,2)+pow(valdist,2));
  return dist;
}
