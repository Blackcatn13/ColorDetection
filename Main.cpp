#include "Kmeans.h"
#include "CImg.h"

#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include <fstream>

#include "InitVectorsFunctions.h"
// Includes of the new Point types
#include "CIELABPoint.h"
#include "RGBAPoint.h"
#include "HSVPoint.h"

//Compilation in linux system:
//g++ -o main CIELABPoint.cpp CIELABPoint.h CImg.h DPoint.cpp DPoint.h HSVPoint.cpp HSVPoint.h InitVectorsFunctions.cpp InitVectorsFunctions.h  Kmeans.cpp Kmeans.h Main.cpp RGBAPoint.cpp RGBAPoint.h Set.cpp Set.h  -O2 -L/usr/X11R6/lib -lm -lpthread -lX11 && ./main

enum Color_names {white = 0, pink, red, orange, brown, yellow, grey, green, blue, purple, black};
using namespace std;
using namespace cimg_library;

// Function to compare two ints
bool comp (int first, int second) { return second<first;}
// Function to compare two *DPoints
bool compareDPoint(DPoint *p1, DPoint *p2) {return *p1 < *p2;}
// Function that return equality from *DPoint
bool sameDPoint(DPoint *p1, DPoint *p2) {return *p1 == *p2;}
// Functions used by main
void printtime(double time);
void printMenu();
vector<string> imageAnalysis(bool Rep, bool Verbose);
Set getSet(int PointType, bool Repetitions);
// Funtion that prints the list of the 4 most used colors in the image
vector<string> printcolors(vector<DPoint*>);
int getminordistance(DPoint *p);

// Set to be used in the other functions
vector<Set> globalSet;
// Variable that holds the image
CImg<float> img;
// Variables of for the menu and the program
string filename = "Images/Image000.bmp";
int PointType = 0;
int k = 5;
// Vector with the 11 colors in the diferent spaces
vector<DPoint*> ColorSpace;

// Main function
int main(){
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
          cout << "0- " << "DPoint with eucledian distance and RGB Defacto Colors" << endl;
          cout << "1- " << "CIELABPoint with eucledian distance and LAB Defacto Colors" << endl;
          cout << "2- " << "CIELABPoint with eucledian distance and LAB Experimental Colors" << endl;
          cout << "7- " << "RGBAPoint with eucledian distance and RGB Experimental Colors" << endl;
          cout << "8- " << "HSVPoint with euclidian distance and HSV Defacto Colors" << endl;
          cin >> PointType;
          break;
      case 4:
          imageAnalysis(false, false);
          break;
      case 5:
          imageAnalysis(true, false);
          break;
      case 6:
          imageAnalysis(false, false);
          break;
      case 7:
          imageAnalysis(true, true);
          break;
      case 8:
          int numImg = -1;
          stringstream ss;
          vector<string> output;
          cout << "Start entire image folder - Caution! May be slower -" << endl;
          cout << "Insert the number of images" << endl;
          cin >> numImg;
          cout << "Insert type of image analysis" << endl;
          cout << "1- " << "Start color identification " << endl;
          cout << "2- " << "Start color identification with verbose mode " << endl;
          cout << "3- " << "Start color identification without color repetitions" << endl;
          cout << "4- " << "Start color identification with verbose mode without color repetitions " << endl;
          int mode;
          cin >> mode;
          bool Rep, Verbose;
          switch (mode){
          case 1:
              Rep = true;
              Verbose = false;
              break;
          case 2:
              Rep = true;
              Verbose = true;
              break;
          case 3:
              Rep = false;
              Verbose = false;
              break;
          case 4:
              Rep = false;
              Verbose = true;
              break;
          }
          ofstream file;
          try{
            file.open("output.txt");
            file << "/*****************************************************/" << "\n";
            file << "Operation mode" << "\n";
            file << "K value: " << k << "\t" << "Point type: " << PointType << "\n";
            file << "Repetitions: " << Rep << "\t" << "Verbose: " << Verbose << "\n";
            file << "/*****************************************************/" << "\n\n";
            for (int i=0; i < numImg; i++){
                filename.clear();
                if (i < 10)
                    filename.append("Images/Image00");
                else
                    filename.append("Images/Image0");
                ss.str("");
                ss << i;
                filename.append(ss.str());
                filename.append(".bmp");
                try{
                  img.load(filename.c_str());
                  output = imageAnalysis(Rep,Verbose);
                  for (int j = 0; j < output.size(); j++){
                    file << output[j];
                    file << "\t";
                  }
                  file << "\n";
                  output.clear();
                }catch(...){
                }
            }
            file.close();
          }catch(...){
            cout << "Error creating file output.txt" << endl;
          }
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
    cout << "8- " << "Start entire image folder - Caution! May be slower -" << endl;
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
    case 2:
        imgAux.RGBtoLab();
        p = new CIELABPoint();
        break;
    case 7:
        p = new RGBAPoint();
        break;
    case 8:
        p = new HSVPoint();
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
            case 2:
                p = new CIELABPoint();
                break;
            case 7:
                p = new RGBAPoint();
                break;
            case 8:
                p = new HSVPoint();
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
        removequals.sort(compareDPoint);
        removequals.unique(sameDPoint);
        vector<DPoint*> vecaux = vector<DPoint*>(removequals.begin(), removequals.end());
        Set setAux = Set();
        for(int i = 0; i < vecaux.size(); i++){
            setAux.addPoint(vecaux[i]);
        }
        return setAux;
    }
}

vector<string> printcolors(vector<DPoint*> v){
  vector<int> colors = vector<int>();

  switch(PointType){
  case 0:
      ColorSpace = initDefault();
      break;
  case 1:
      ColorSpace = initDefactoCIELAB();
      break;
  case 2:
      ColorSpace = initCIELAB();
      break;
  case 7:
      ColorSpace = initRGB();
      break;
  case 8:
      ColorSpace = initHSV();
      break;
  }

  colors.resize(ColorSpace.size());
  int j = 0;
  for(int i = 0; i < v.size(); i++){
    j = getminordistance(v[i]);
    colors[j] += globalSet[i].getPoints().size();
  }

  bool(*fn_pt)(int,int) = comp;
  multimap<int,Color_names, bool(*) (int,int)> color (fn_pt);
  multimap<int,Color_names, bool(*) (int,int)>::iterator it;
  for (int i = 0; i < colors.size(); i++){
      color.insert(pair<int, Color_names>(colors[i],Color_names(i)));
  }
  int count = 0;
  it = color.begin();
  vector<string> output;
  bool next;
  do{
      switch(it->second){
      case white:
          output.push_back("White");
          break;
      case pink:
          output.push_back("Pink");
          break;
      case red:
          output.push_back("Red");
          break;
      case orange:
          output.push_back("Orange");
          break;
      case brown:
          output.push_back("Brown");
          break;
      case yellow:
          output.push_back("Yellow");
          break;
      case grey:
          output.push_back("Grey");
          break;
      case green:
          output.push_back("Green");
          break;
      case blue:
          output.push_back("Blue");
          break;
      case purple:
          output.push_back("Purple");
          break;
      case black:
          output.push_back("Black");
          break;
      }
      count++;
      it++;
      next = ((count < 4) && (it->first != 0));
  } while(next);
  return output;
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

//Image analysis
vector<string> imageAnalysis(bool Rep, bool Verbose){
    vector<string> output;
    // Kmeans class var
    Kmeans km;
    // Var to calculate time of ejecution
    clock_t c;
    cout << "Start color identification ";
    if (Rep)
        cout << "with repetitions ";
    else
        cout << "without repetitions ";
    if (Verbose)
        cout << "with verbose ";
    else
        cout << "without verbose";
     cout << endl;
    c = clock();
    km = Kmeans(getSet(PointType, true));
    try{
      globalSet = km.Calculate(k, Rep);
    } catch (int e){
        cout << "New k: " << k-e << endl;
        globalSet = km.Calculate(k-e, Verbose);
    }
    output = printcolors(km.getInertiaCenter());
    cout << "Colors: ";
    for (int i = 0; i < output.size(); i++){
      cout << output[i] << " ";
    }
    cout << endl;
    printtime(((double)clock() - c) / CLOCKS_PER_SEC);
    cout << endl;
    return output;
}
