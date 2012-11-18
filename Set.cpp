#include "Set.h"

#include "iostream"

// Default Constructor of the class
Set::Set(){
  Points = vector<DPoint*>();
}
// Function to add a Point to the set
void Set::addPoint(DPoint *p){
  Points.push_back(p);
}

// Function to compare to DPoint pointers
bool compare(DPoint *p1, DPoint *p2){
    return *p1 < *p2;
}

// Funtion to return equality between to DPoint pointers
bool same(DPoint *p1, DPoint *p2){
    return *p1 == *p2;
}

// Funtion that returns k random points
vector<DPoint*> Set::getRandomPoints(int k){
  list<DPoint*> removequals = list<DPoint*>(Points.begin(), Points.end());
  removequals.sort(compare);
  removequals.unique(same);
  vector<DPoint*> vecaux = vector<DPoint*>(removequals.begin(), removequals.end());
  random_shuffle(vecaux.begin(), vecaux.end());
  vecaux.resize(k);
  return vecaux;
}

// Function that returns k points using Kaufman algorithm

vector<DPoint*> Set::getKaufmanPoints(int k){
  list<DPoint*> removequals = list<DPoint*>(Points.begin(), Points.end());
  removequals.sort(compare);
  removequals.unique(same);
  vector<DPoint*> vecaux = vector<DPoint*>(removequals.begin(), removequals.end());
  vector<float> sum = vector<float>();
  DPoint* auxPoint = new DPoint();
  int n = vecaux.size();
  for (int j = 0; j < vecaux[0]->getDimension(); j++){
    sum.push_back(vecaux[0]->getPosition()[j]);
  }
  for (int i = 0; i < n; i++){
    for (int j = 0; j < vecaux[0]->getDimension(); j++){
      sum[j] += vecaux[i]->getPosition()[j];
    }
  }
  for (int j = 0; j < vecaux[0]->getDimension(); j++){
    sum[j] = sum[j]/n;
  }
  auxPoint->setPosition(sum);
  // Calculate the nearest point to ideal center
  DPoint* minPoint = new DPoint();
  float distance = 1e32;
  float ndistance;

  for(int i = 0; i < n; i++){
    ndistance = vecaux[i]->Distance(auxPoint);
    if(ndistance < distance){
      minPoint = vecaux[i];
      distance = ndistance;
    }
  }
  vector<float> minPos= minPoint->getPosition();
  for (int i = 0; i < minPos.size(); i++){
    cout << minPos[i] << " ";
  }
  cout << endl;
    //vector<float> auxPoint = vecaux[i]->getPosition();
    //cout << auxPoint[0] << " " << auxPoint[1] << " " << auxPoint[2] << endl;
  return vecaux;
}
