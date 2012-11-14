#include "RGBAPoint.h"

RGBAPoint::RGBAPoint(){
}

float RGBAPoint::Distance(DPoint *p){
  float dist = 0;
  float kl = 1;
  float k1 = 0.045;
  float k2 = 0.015;
  float kc = 1;
  float kh = 1;
  for(int i = 0; i < p->getDimension(); i++){
    dist += pow((double)(Position[i] - p->getPosition()[i]), 2);
  }
  dist = sqrt(dist);
  /*float al, c1, c2, ac, ah, aa, ab, sl, sc, sh;
  al = Position[0] - p->getPosition()[0];
  c1 = sqrt(pow((double)Position[1], 2) + pow((double)Position[2], 2));
  c2 = sqrt(pow((double)p->getPosition()[1], 2) + pow((double)p->getPosition()[2], 2));
  ac = c1 - c2;
  aa = Position[1] - p->getPosition()[1];
  ab = Position[2] - p->getPosition()[2];
  ah = sqrt(pow((double)aa, 2) + pow((double)ab,2) - pow((double)ac,2));
  sl = 1;
  sc = 1 + k1*c1;
  sh = 1 + k2*c1;
  dist += pow((double)(al/(kl*sl)),2);
  dist += pow((double)(ac/(kc*sc)),2);
  dist += pow((double)(ah/(kh*sh)),2);
  dist = sqrt(dist);*/
  
  return dist;
}