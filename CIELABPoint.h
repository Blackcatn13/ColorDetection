#ifndef CIELABPoint_H
#define CIELABPoint_H

#include "DPoint.h"
// Class that represents a point in the CIELab Dimension
class CIELABPoint: public DPoint{
public:
  CIELABPoint();
  virtual float Distance(DPoint *p);
};

#endif