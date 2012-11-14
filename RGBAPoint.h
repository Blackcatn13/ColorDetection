#ifndef RGBAPoint_H
#define RGBAPoint_H

#include "DPoint.h"

class RGBAPoint: public DPoint{
public:
  RGBAPoint();
  virtual float Distance(DPoint *p);
};

#endif