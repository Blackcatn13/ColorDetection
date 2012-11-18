#include "Kmeans.h"

// Default constructor of the class
Kmeans::Kmeans(){
  Points = vector<DPoint*>();
  InitialSet = Set();
  // Delete unused pointers
  for(int i = 0; i < InertiaCenter.size(); i++){
      delete InertiaCenter[i];
  }
  for(int i = 0; i < InitialSet.getPoints().size(); i++){
      delete InitialSet.getPoints()[i];
  }
}
// Constructor that takes a set
Kmeans::Kmeans(Set s){
  // Delete unused pointers
  for(int i = 0; i < InitialSet.getPoints().size(); i++){
    delete InitialSet.getPoints()[i];
  }
  InitialSet = s;
  Points = s.getPoints();
  // Delete unused pointers
  for(int i = 0; i < InertiaCenter.size(); i++){
      delete InertiaCenter[i];
  }
}
// Function that calculate the K-Mean algorithm returning the clusters
vector<Set> Kmeans::Calculate(int k, bool verbose){
  int loops = 0;
  clock_t c;
  bool equal = false;
  // We get the first random inertia center for the point set 
  //InertiaCenter = InitialSet.getRandomPoints(k);
  InertiaCenter = InitialSet.getKaufmanPoints(k);
  if(verbose) {
    cout << "The number of points is: " << Points.size() << endl;
  }
  // While the actual inertia center is diferent that the t-1 inertia center we make another loop
  do{
    if(verbose) {
    cout << "Loop n: " << loops << endl;
    c = clock();
    }
    ClearClass(k);
    // We add every point in the cluster with the minium distance to the inertia point
    for(int i = 0; i < Points.size(); i++){
      Class[PosMinDistance(Points[i])].addPoint(Points[i]);
    }

    OldInertiaCenter = InertiaCenter;
    // We calculate the new inertia center from the points in the cluster
    try{
        InertiaCenter = getNewInertiaCenters();
    }
    catch (int e){
        cout << endl << "One cluster is empty, trying with a minor k " << endl;
        throw e;
    }
    equal = equals(OldInertiaCenter, InertiaCenter);
    if(verbose){
      Printime(((double)clock() - c) / CLOCKS_PER_SEC);
      cout << "New loop? " << !equal << endl;
      loops++;
    }
    // We repeat the loop while the Inertia Center is diferent with the previous Inertia Center
  } while(!equal);

  return Class;
}
// Function that returns in witch cluster the given point has to go
int Kmeans::PosMinDistance(DPoint *point){
  int m = 0;
  int distance = 1e32;
  int ndistance;

  for(int i = 0; i < InertiaCenter.size(); i++){
    ndistance = point->Distance(InertiaCenter[i]);
    if(ndistance < distance){
      m = i;
      distance = ndistance;
    }
  }
  return m;
}
// Function that returns a new inertia center for a given cluster
DPoint* Kmeans::getNewInertiaCenter(vector<DPoint*> points){
  vector<float> position;

  // If one of the clusters is empty we throw an exception
  if(points.size() == 0){
      throw 1;
  }
  position.resize(points[0]->getDimension());
  for(int i = 0; i < points.size(); i++){
    for(int j = 0; j < points[0]->getDimension(); j++){
      position[j] += points[i]->getPosition()[j];
    }
  }
  for(int i = 0; i < points[0]->getDimension(); i++){
    position[i] /= points.size();
  }
  DPoint *point = new DPoint();
  point->setPosition(position);
  return point;
}
// Function that returns all the new inertia center of the given clusters
vector<DPoint*> Kmeans::getNewInertiaCenters(){
  vector<DPoint*> Inertia;
  try{
      for(int i = 0; i < Class.size(); i++){
        Inertia.push_back(getNewInertiaCenter(Class[i].getPoints()));
      }
      return Inertia;
  }
  // If an exception ocurred we return the number of empty cluster to try with a minor k
  catch (int e){
      int ceros = 0;
      for(int i = 0; i < Class.size(); i++){
          if(Class[i].getPoints().size() == 0){
              ceros++;
          }
      }
      throw ceros;
  }
}
// Function to reset the cluster to begin a new loop
void Kmeans::ClearClass(int k){
  Class.erase(Class.begin(), Class.end());
  for(int i = 0; i < k; i++){
    Class.push_back(Set());
  }
}
// Function to print the time between loops if mode verbose used
void Kmeans::Printime(double Time){
  cout << "Time elapsed: " << (int)(Time / 60) << " m " << (int)Time % 60 << " s " << endl;
  cout << "T (s): " << Time << endl;

}
// Function that return true if the to vectors are equals
bool Kmeans::equals(vector<DPoint*> v1, vector<DPoint*> v2){
    for(int i = 0; i < v1.size(); i++){
        if(*v1[i] != *v2[i]){
            return false;
        }
    }
    return true;
}
