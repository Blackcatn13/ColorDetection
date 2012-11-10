#ifndef CIELABPoint_H
#define CIELABPoint_H

#include "DPoint.h"

class CIELABPoint: public DPoint{
public:
  CIELABPoint();
  virtual float Distance(DPoint *p);
};

#endif