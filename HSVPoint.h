#ifndef HSVPoint_H
#define HSVPoint_H

#include "DPoint.h"
#include "math.h"
#define PI 3.14159265

class HSVPoint: public DPoint{
public:
  HSVPoint();
  virtual float Distance(DPoint *p);
};

#endif
