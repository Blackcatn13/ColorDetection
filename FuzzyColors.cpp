#include "FuzzyColors.h"

int getminordistance(DPoint *point, vector<pair<CIELABPoint,vector<float> > > points);
int getminordistance(DPoint *point, vector<pair<RGBAPoint,vector<float> > > points);

vector<int> getFuzzyCIELAB(vector<DPoint*> points, vector<Set> globalSet){
    ifstream file;
    string line;
    stringstream stream;
    file.open("mv_Lab.txt");
    vector<pair<CIELABPoint,vector<float> > > CIELABvalues;
    vector<int> colorSum;
    vector<float> position;
    vector<float> values;
    float aux;
    CIELABPoint p = CIELABPoint();

    while(!file.eof()){
        getline(file, line);
        stream.clear();
        stream << line;
        position.clear();
        for(int i = 0; i < 3; i++){
            stream >> aux;
            position.push_back(aux);
        }
        p.setPosition(position);
        values.clear();
        for(int i = 0; i < 11; i++){
            stream >> aux;
            values.push_back(aux);
        }
        CIELABvalues.push_back(pair<CIELABPoint,vector<float> >(p,values));
    }   
    file.close();
    int j = 0;
    colorSum.resize(11);
    for(int i = 0; i < points.size(); i++){
        j = getminordistance(points[i],CIELABvalues);
        for(int x = 0; x < 11; x++){
            colorSum[x] += CIELABvalues[j].second[x] * globalSet[i].getPoints().size();
        }
    }
  
    return colorSum;
}

vector<int> getFuzzyRGB(vector<DPoint*> points, vector<Set> globalSet){
    ifstream file;
    string line;
    stringstream stream;
    vector<int> colorSum;
    try{
      file.open("mv_RGB.txt");
      vector<pair<RGBAPoint,vector<float> > > RGBAvalues;
      vector<float> position;
      vector<float> values;
      float aux;
      RGBAPoint p = RGBAPoint();
      while(!file.eof()){
          getline(file, line);
          stream.clear();
          stream << line;
          position.clear();
          for(int i = 0; i < 3; i++){
              stream >> aux;
              position.push_back(aux);
          }
          p.setPosition(position);
          values.clear();
          for(int i = 0; i < 11; i++){
              stream >> aux;
              values.push_back(aux);
          }
          RGBAvalues.push_back(pair<RGBAPoint,vector<float> >(p,values));
      }
      file.close();
      int j = 0;
      colorSum.resize(11);
      for(int i = 0; i < points.size(); i++){
          j = getminordistance(points[i],RGBAvalues);
          for(int x = 0; x < 11; x++){
              colorSum[x] += RGBAvalues[j].second[x] * globalSet[i].getPoints().size();
          }
      }
    }catch(...){
  }
  return colorSum;
}


int getminordistance(DPoint *point, vector<pair<CIELABPoint,vector<float> > > points){

  int m = 0;
  int distance = 1e32;
  int ndistance;

  for(int i = 0; i < points.size(); i++){
      ndistance = point->Distance(&(DPoint)points[i].first);
    if(ndistance < distance){
      m = i;
      distance = ndistance;
    }
  }
  return m;
}

int getminordistance(DPoint *point, vector<pair<RGBAPoint,vector<float> > > points){

  int m = 0;
  int distance = 1e32;
  int ndistance;

  for(int i = 0; i < points.size(); i++){
      ndistance = point->Distance(&(DPoint)points[i].first);
    if(ndistance < distance){
      m = i;
      distance = ndistance;
    }
  }
  return m;
}
