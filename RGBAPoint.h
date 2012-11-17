#ifndef RGBAPoint_H
#define RGBAPoint_H

#include "DPoint.h"
// Class that represents a point in the RGB Dimension
class RGBAPoint: public DPoint{
public:
  RGBAPoint();
  virtual float Distance(DPoint *p);
};

#endif