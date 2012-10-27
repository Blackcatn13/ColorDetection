#ifndef DPoint_H
#define DPoint_H

#include <math.h>
#include <vector>

using namespace std;
// Class that represents a point in the n-Dimension
class DPoint{
  vector<float> Position;
public:
  DPoint();
  int getDimension() {return Position.size();}
  vector<float> getPosition() {return Position;}
  void setPosition(vector<float> nposition);
  virtual float Distance(DPoint p);
  bool operator== (const DPoint &p);
  bool operator!= (const DPoint &p);
};

#endif