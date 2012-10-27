#include "Kmeans.h"

// Default constructor of the class
Kmeans::Kmeans(){
  Points = vector<DPoint>();
  InitialSet = Set();
}
// Constructor that takes a set
Kmeans::Kmeans(Set s){
  InitialSet = s;
  Points = s.getPoints();
}
// Function that calculate the K-Mean algorithm returning the clusters
vector<Set> Kmeans::Calculate(int k){
  bool equals = false;
  // We get the first random inertia center for the point set 
  InertiaCenter = InitialSet.getRandomPoints(k);
  // While the actual inertia center is diferent that the t-1 inertia center we make another loop
  do{
    ClearClass(k);
    // We add every point in the cluster with the minium distance to the inertia point
    for(int i = 0; i < Points.size(); i++){
      Class[PosMinDistance(Points[i])].addPoint(Points[i]);
    }
    OldInertiaCenter = InertiaCenter;
    // We calculate the new inertia center from the points in the cluster
    InertiaCenter = getNewInertiaCenters();
    equals = std::equal(OldInertiaCenter.begin(), OldInertiaCenter.end(), InertiaCenter.begin());
  } while(!equals);
  return Class;
}
// Function that returns in witch cluster the given point has to go
int Kmeans::PosMinDistance(DPoint point){
  int m = 0;
  int distance = 1e32;
  int ndistance;

  for(int i = 0; i < InertiaCenter.size(); i++){
    ndistance = point.Distance(InertiaCenter[i]);
    if(ndistance < distance){
      m = i;
      distance = ndistance;
    }
  }
  return m;
}
// Function that returns a new inertia center for a given cluster
DPoint Kmeans::getNewInertiaCenter(vector<DPoint> points){
  vector<float> position;
  position.resize(points[0].getDimension());
  for(int i = 0; i < points.size(); i++){
    for(int j = 0; j < points[0].getDimension(); j++){
      position[j] += points[i].getPosition()[j];
    }
  }
  for(int i = 0; i < points[0].getDimension(); i++){
    position[i] /= points.size();
  }
  DPoint point = DPoint();
  point.setPosition(position);
  return point;
}
// Function that returns all the new inertia center of the given clusters
vector<DPoint> Kmeans::getNewInertiaCenters(){
  vector<DPoint> Inertia;
  for(int i = 0; i < Class.size(); i++){
    Inertia.push_back(getNewInertiaCenter(Class[i].getPoints()));
  }
  return Inertia;
}
// Function to reset the cluster to begin a new loop
void Kmeans::ClearClass(int k){
  Class.erase(Class.begin(), Class.end());
  for(int i = 0; i < k; i++){
    Class.push_back(Set());
  }
}