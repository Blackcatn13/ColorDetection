#include <iostream>
#include "Kmeans.h"
#include <CImg.h>
#include <time.h>
#include <string>
// Includes of the new Point types
#include "CIELABPoint.h"
#include "RGBAPoint.h"

using namespace std;
using namespace cimg_library;

// Functions used by main
void printtime(double time);
void printMenu();
Set getSet(int PointType, bool Repetitions);
// Funtion that prints the list of the 4 most used colors in the image
void printcolors(vector<DPoint*>);
int getminordistance(DPoint *p);
// Functions to init the 11 colors in the diferent spaces
vector<DPoint*> initRGBA();
vector<DPoint*> initCIELAB();
vector<DPoint*> initDefault();

// Set to be used in the other functions
vector<Set> globalSet;
// Variable that holds the image
CImg<float> img;
// Variables of for the menu and the program
string filename = "Images/16243.bmp";
int PointType = 0;
int k = 4;
// Vector with the 11 colors in the diferent spaces
vector<DPoint*> ColorSpace;

// Main function
int main(){
  // Var to calculate time of ejecution
  clock_t c;
  // Kmeans class var
  Kmeans km;
  img.load(filename.c_str());
  // Variable for the menu options
  int menu = 0;
  string aux;
  do{
      printMenu();
      cin >> menu;
      cin.clear();

      switch(menu){
      case 1:
          cout << "Input the name of the new file to load: " << endl;
          filename.clear();
		  filename.append("Images/");
		  cin >> aux;
		  filename.append(aux);
		  filename.append(".bmp");
          try{
            img.load(filename.c_str());
          }
          catch(...){

          }
          break;
      case 2:
          cout << "Input the new K: " << endl;
          cin >> k;
          break;
      case 3:
          cout << "Input the new Point type: " << endl;
          cout << "0- " << "DPoint with eucledian distance " << endl;
          cout << "1- " << "CIELABPoint with eucledian distance " << endl;
		  cout << "7- " << "RGBAPoint with eucledian distance " << endl;
          cin >> PointType;
          break;
      case 4:
          cout << "Starting color identification " << endl;
          c = clock();
          km = Kmeans(getSet(PointType, true));
          globalSet = km.Calculate(k, false);
          printtime(((double)clock() - c) / CLOCKS_PER_SEC);
          printcolors(km.getInertiaCenter());
          cout << endl;
          break;
      case 5:
          cout << "Start color identification with verbose mode " << endl;
          c = clock();
          km = Kmeans(getSet(PointType, true));
          globalSet = km.Calculate(k, true);
          printtime(((double)clock() - c) / CLOCKS_PER_SEC);
          printcolors(km.getInertiaCenter());
          cout << endl;
          break;
      case 6:
          cout << "Start color identification without color repetitions " << endl;
          c = clock();
          km = Kmeans(getSet(PointType, false));
          globalSet = km.Calculate(k, false);
          printtime(((double)clock() - c) / CLOCKS_PER_SEC);
          printcolors(km.getInertiaCenter());
          cout << endl;
          break;
      case 7:
          cout << "Start color identification with verbose mode without color repetitions " << endl;
          c = clock();
          km = Kmeans(getSet(PointType, false));
          globalSet = km.Calculate(k, true);
          printtime(((double)clock() - c) / CLOCKS_PER_SEC);
          printcolors(km.getInertiaCenter());
          cout << endl;
          break;
     }
    
  }while(menu != 9);

  return 0;
}

void printtime(double time){
  cout << "Time elapsed: " << (int)(time / 60) << " m " << (int)time % 60 << " s " << endl;
  cout << "T (s): " << time << endl;
}

void printMenu(){
    cout << endl;
    cout << "Welcom to the Menu " << endl;
    cout << "1- " << "Specify file name " << "(Now loaded " << filename << ") " << endl;
    cout << "2- " << "Specify K " << "(Now is " << k << ") " << endl;
    cout << "3- " << "Specify Point type " << "(Now is " << PointType << ") "<< endl;
    cout << "4- " << "Start color identification " << endl;
    cout << "5- " << "Start color identification with verbose mode " << endl;
    cout << "6- " << "Start color identification without color repetitions " << endl;
    cout << "7- " << "Start color identification with verbose mode without color repetitions " << endl;
    cout << "9- " << "Exit " << endl;

}

Set getSet(int PointType, bool Repetitions){
    Set imgPoints = Set();
    DPoint *p;
    vector<float> position = vector<float>();
    CImg<float> imgAux = img;
    switch(PointType){
    case 0:
        p = new DPoint();
        break;
    case 1: 
        imgAux.RGBtoLab();
        p = new CIELABPoint();
        break;
	case 7: 
        p = new RGBAPoint();
        break;
    }

    for(int i = 0; i < imgAux.height(); i++){
        for(int j = 0; j < imgAux.width(); j++){
            position.push_back(imgAux(j, i, 0, 0));
            position.push_back(imgAux(j, i, 0, 1));
            position.push_back(imgAux(j, i, 0, 2));
            p->setPosition(position);
            imgPoints.addPoint(p);
            position.erase(position.begin(), position.end());
            switch(PointType){
            case 0:
                p = new DPoint();
                break;
            case 1:
                p = new CIELABPoint();
                break;
			case 7:
                p = new RGBAPoint();
                break;
            }
        }
    }

    if(Repetitions){
        return imgPoints;
    }
    else{
        vector<DPoint*> aux = imgPoints.getPoints();
        list<DPoint*> removequals = list<DPoint*>(aux.begin(), aux.end());
        removequals.sort();
        removequals.unique();
        vector<DPoint*> vecaux = vector<DPoint*>(removequals.begin(), removequals.end());
        Set setAux = Set();
        for(int i = 0; i < vecaux.size(); i++){
            setAux.addPoint(vecaux[i]);
        }
        return setAux;
    }
}

void printcolors(vector<DPoint*> v){
  vector<int> colors = vector<int>();

  switch(PointType){
  case 0:
      ColorSpace = initDefault();
      break;
  case 1:
      ColorSpace = initCIELAB();
      break;
  case 7:
      ColorSpace = initRGBA();
      break;
  }
  colors.resize(ColorSpace.size());
  int j=0;
  for(int i = 0; i < v.size(); i++){
    j = getminordistance(v[i]);
    colors[j] += globalSet[i].getPoints().size();
  }

  cout << endl << "The list of repetitions in this foto is :" << endl;

  for(int i = 0; i < colors.size(); i++){
    switch(i){
    case 0:
      cout << "- White colors: " << colors[i] << endl;
      break;
    case 1:
      cout << "- Pink colors: " << colors[i] << endl;
      break;
    case 2:
      cout << "- Red colors: " << colors[i] << endl;
      break;
    case 3:
      cout << "- Orange colors: " << colors[i] << endl;
      break;
    case 4:
      cout << "- Brown colors: " << colors[i] << endl;
      break;
    case 5:
      cout << "- Yellow colors: " << colors[i] << endl;
      break;
    case 6:
      cout << "- Grey colors: " << colors[i] << endl;
      break;
    case 7:
      cout << "- Green colors: " << colors[i] << endl;
      break;
    case 8:
      cout << "- Blue colors: " << colors[i] << endl;
      break;
    case 9:
      cout << "- Purple colors: " << colors[i] << endl;
      break;
    case 10:
      cout << "- Black colors: " << colors[i] << endl;
      break;
    }
  }
}

int getminordistance(DPoint *point){
  int m = 0;
  int distance = 1e32;
  int ndistance;

  for(int i = 0; i < ColorSpace.size(); i++){
    ndistance = point->Distance(ColorSpace[i]);
    if(ndistance < distance){
      m = i;
      distance = ndistance;
    }
  }
  return m;
}

vector<DPoint*> initDefault(){
    /* 0 - white r = 255, g = 255, b = 255
      1 - pink r = 255, g = 192, b = 203
      2 - red r = 255, g = 0, b = 0
      3 - orange r = 255, g = 127, b = 0
      4 - brown r = 150, g = 75, b = 0
      5 - yellow r = 255, g = 255, b = 0
      6 - grey  r = 128, g = 128, b = 128
      7 - green r = 0, g = 255, b = 0
      8 - blue r = 0, g = 0, b = 255
      9 - purple r = 143, g = 0, b = 255
      10- black r = 0, g = 0, b = 0
      */
    return vector<DPoint*>();
}

vector<DPoint*> initRGBA(){
      /* 0 - white r = 255, g = 255, b = 255
      1 - pink r = 255, g = 192, b = 203
      2 - red r = 255, g = 0, b = 0
      3 - orange r = 255, g = 127, b = 0
      4 - brown r = 150, g = 75, b = 0
      5 - yellow r = 255, g = 255, b = 0
      6 - grey  r = 128, g = 128, b = 128
      7 - green r = 0, g = 255, b = 0
      8 - blue r = 0, g = 0, b = 255
      9 - purple r = 143, g = 0, b = 255
      10- black r = 0, g = 0, b = 0
      */
  vector<DPoint*> RGBAcolors = vector<DPoint*>();
  DPoint *p = new DPoint();
  vector<float> pos = vector<float>();
  //0 - white r=255, g=255, b=255
  pos.push_back(220);
  pos.push_back(220);
  pos.push_back(220);
  p->setPosition(pos);
  RGBAcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  // 1 - pink r = 255, g = 192, b = 203
  pos.push_back(220);
  pos.push_back(190);
  pos.push_back(200);
  p->setPosition(pos);
  RGBAcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //2 - red r = 255, g = 0, b = 0
    pos.push_back(220);
  pos.push_back(0);
  pos.push_back(0);
  p->setPosition(pos);
  RGBAcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //3 - orange r = 255, g = 127, b = 0
    pos.push_back(220);
  pos.push_back(120);
  pos.push_back(0);
  p->setPosition(pos);
  RGBAcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //4 - brown r = 150, g = 75, b = 0
    pos.push_back(130);
  pos.push_back(70);
  pos.push_back(0);
  p->setPosition(pos);
  RGBAcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //5 - yellow r = 255, g = 255, b = 0
  pos.push_back(220);
  pos.push_back(220);
  pos.push_back(0);
  p->setPosition(pos);
  RGBAcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //6 - grey  r = 128, g = 128, b = 128
    pos.push_back(90);
  pos.push_back(90);
  pos.push_back(90);
  p->setPosition(pos);
  RGBAcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //7 - green r = 0, g = 255, b = 0
  pos.push_back(0);
  pos.push_back(220);
  pos.push_back(0);
  p->setPosition(pos);
  RGBAcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //8 - blue r = 0, g = 0, b = 255
    pos.push_back(0);
  pos.push_back(0);
  pos.push_back(220);
  p->setPosition(pos);
  RGBAcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //9 - purple r = 143, g = 0, b = 255
    pos.push_back(120);
  pos.push_back(0);
  pos.push_back(220);
  p->setPosition(pos);
  RGBAcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  // 10- black r = 0, g = 0, b = 0
    pos.push_back(10);
  pos.push_back(10);
  pos.push_back(10);
  p->setPosition(pos);
  RGBAcolors.push_back(p);
  pos.erase(pos.begin(), pos.end());
  return RGBAcolors;
}


vector<DPoint*> initCIELAB(){
     /* 0 - white l = 100, a = 0, b = 0
      1 - pink l = 83.585, a = 24.15, b = 3.315
      2 - red l = 53.233, a = 80.109, a = 67.220
      3 - orange l=66.854, a =43.324, b =73.910
      4 - brown l=40.437, a = 27.502, b=50.147
      5 - yellow l=97.138, a=-21.556, b=94.482
      6 - grey  l=53.585, a = 0, b = 296.813
      7 - green l=87.737, a = -86.185, b=83.181
      8 - blue l=32.303, a=79.197, b=-107.864
      9 - purple l=29.782, a=58.940, b=-36.498
      10- black l=0, a=0, b=0*/
  vector<DPoint*> labcolors = vector<DPoint*>();
  DPoint *p = new DPoint();
  vector<float> pos = vector<float>();
  //0 - white l = 100, a = 0, b = 0
  pos.push_back(100);
  pos.push_back(0);
  pos.push_back(0);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //1 - pink l = 83.585, a = 24.15, b = 3.315
  pos.push_back(89.745);
  pos.push_back(16.025);
  pos.push_back(-1.815);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //2 - red l = 53.233, a = 80.109, a = 67.220
    pos.push_back(60.460);
  pos.push_back(59.572);
  pos.push_back(25.153);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //3 - orange l=66.854, a =43.324, b =73.910
    pos.push_back(80.732);
  pos.push_back(16.248);
  pos.push_back(48.706);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //    4 - brown l=40.437, a = 27.502, b=50.147
    pos.push_back(77.344);
  pos.push_back(9.679);
  pos.push_back(18.265);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //    5 - yellow l=97.138, a=-21.556, b=94.482
    pos.push_back(98.59);
  pos.push_back(-10.217);
  pos.push_back(32.201);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //    6 - grey  l=53.585, a = 0, b = 296.813
    pos.push_back(50.0);
  pos.push_back(0);
  pos.push_back(0);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //    7 - green l=87.737, a = -86.185, b=83.181
    pos.push_back(82.190);
  pos.push_back(-36.099);
  pos.push_back(29.940);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //    8 - blue l=29, a=73, b=-100
    pos.push_back(91.635);
  pos.push_back(-7.213);
  pos.push_back(-4.322);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //    9 - purple l=29.782, a=58.940, b=-36.498
    pos.push_back(44.498);
  pos.push_back(77.867);
  pos.push_back(-48.214);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //    10- black l=0, a=0, b=0
    pos.push_back(0);
  pos.push_back(0);
  pos.push_back(0);
  p->setPosition(pos);
  labcolors.push_back(p);
  pos.erase(pos.begin(), pos.end());
  return labcolors;
}


