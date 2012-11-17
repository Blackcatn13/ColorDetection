#include "FuzzyColors.h"

vector<int> getFuzzyCIELAB(vector<DPoint*> points){
    return vector<int>();



}

vector<int> getFuzzyRGB(vector<DPoint*> points, vector<Set> set){
  try{
    ifstream file;
    file.open("mv_RGB.txt");
    string line;
    while(!file.eof()){
      getline(file, line);
      cout << line << endl;
    }
    file.close();
  }catch(...){
    cout << "The file can't be readed!" << endl;
  }

  return vector<int>();

}
