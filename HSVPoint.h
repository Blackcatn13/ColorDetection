#ifndef HSVPoint_H
#define HSVPoint_H

#include "DPoint.h"
#include "math.h"

class HSVPoint: public DPoint{
public:
  HSVPoint();
  virtual float Distance(DPoint *p);
};

#endif
