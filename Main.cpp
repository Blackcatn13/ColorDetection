#include "Kmeans.h"
#include "CImg.h"

#include <string>
#include <map>
#include <sstream>
#include <fstream>

#include "InitVectorsFunctions.h"
#include "FuzzyColors.h"
// Includes of the new Point types
#include "CIELABPoint.h"
#include "RGBAPoint.h"

//Compilation in linux system:
/*g++ -o main CIELABPoint.cpp CIELABPoint.h CImg.h DPoint.cpp DPoint.h 
  HSVPoint.cpp HSVPoint.h InitVectorsFunctions.cpp InitVectorsFunctions.h  
  Kmeans.cpp Kmeans.h Main.cpp RGBAPoint.cpp RGBAPoint.h Set.cpp Set.h  -O2 
  -L/usr/X11R6/lib -lm -lpthread -lX11 && ./main */

// Enumeration for the 11 colors
enum Color_names {white = 0, pink, red, orange, brown, yellow, grey, green, blue, purple, black};
using namespace std;
using namespace cimg_library;

// Function to compare two ints
bool comp (int first, int second) { return second<first;}
// Function to compare two DPoints pointers
bool compareDPoint(DPoint *p1, DPoint *p2) {return *p1 < *p2;}
// Function that return equality from DPoint pointers
bool sameDPoint(DPoint *p1, DPoint *p2) {return *p1 == *p2;}

// Functions used by main

// Function to print the elapsed time
void printtime(double time);
// Funtion to show the menu
void printMenu();
// Function that call the k-means with the diferent options
vector<string> imageAnalysis(bool Rep, bool Verbose);
// Function to get the set of points from the file
Set getSet(int PointType, bool Repetitions);
// Funtion that prints the list of the 4 most used colors in the image
vector<string> printcolors(vector<DPoint*>);
// Function to get wich color have minor ditance with the point
int getminordistance(DPoint *p);

// Variables

// Set to be used in the other functions
vector<Set> globalSet;
// Variable that holds the image
CImg<float> img;
// Name of the file
string filename = "Images/16243.bmp";
// Point type to switch in the functions
int PointType = 0;
// K value for the algorithm call
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
          // Change the name of the file to load
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
          // Change the k for the algortihm
      case 2:
          cout << "Input the new K: " << endl;
          cin >> k;
          break;
          // Change the point type
      case 3:
          cout << "Input the new Point type: " << endl;
          cout << "0- " << "DPoint with eucledian distance and RGB Defacto Colors" << endl;
          cout << "1- " << "CIELABPoint with eucledian distance and LAB Defacto Colors" << endl;
          cout << "2- " << "CIELABPoint with eucledian distance and LAB Experimental Colors" << endl;
          cout << "3- " << "CIELABPoint with euclidian distance and fuzzy color naming" << endl;
          cout << "7- " << "RGBPoint with eucledian distance and RGB Experimental Colors" << endl;
          cout << "8- " << "RGBPoint with eucledian distance and fuzzy color naming" << endl;
          cin >> PointType;
          break;
          // Call the algorithm with diferent params
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
          // Function to get all the files from the directory with the name Image0
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
            ss.str("");
            ss << k;
            aux.append("k" + ss.str() + "-");
            ss.str("");
            ss << mode;
            aux.append("op" + ss.str() + "-");
            ss.str("");
            ss << PointType;
            aux.append("p" + ss.str());
            aux.append(".txt");
            file.open(aux.c_str());
	    aux = "";
            //file.open("output.txt");
            file << "/*****************************************************/" << "\n";
            file << "Operation mode" << "\n";
            file << "K value: " << k << "\t" << "Point type: " << PointType << "\n";
            file << "Repetitions: " << Rep << "\t" << "Verbose: " << Verbose << "\n";
            file << "/*****************************************************/" << "\n\n";
            for (int i=0; i < numImg; i++){
                cout << endl << i << endl;
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

// Function that show the time elpased in min sec, and in seconds
void printtime(double time){
  cout << "Time elapsed: " << (int)(time / 60) << " m " << (int)time % 60 << " s " << endl;
  cout << "T (s): " << time << endl;
}

// Function to show the menu
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

// Function to get the initial set
Set getSet(int PointType, bool Repetitions){
    Set imgPoints = Set();
    DPoint *p;
    vector<float> position = vector<float>();
    CImg<float> imgAux = img;
    // Create the new pointer for the diferents points
    switch(PointType){
    case 0:
        p = new DPoint();
        break;
    case 1:
    case 2:
    case 3:
        imgAux.RGBtoLab();
        p = new CIELABPoint();
        break;
    case 7:
    case 8:
        p = new RGBAPoint();
        break;
    }

    // Load the image in the pointers
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
            case 3:
                p = new CIELABPoint();
                break;
            case 7:
            case 8:
                p = new RGBAPoint();
                break;
            }
        }
    }

    // If we don't need to remove repeated points we return the set
    if(Repetitions){
        return imgPoints;
    }
    // We take out the repeated points and return the set
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

// Function that show the 4 predominant colors of the image
vector<string> printcolors(vector<DPoint*> v){
  vector<int> colors = vector<int>();

  for(int i = 0; i < ColorSpace.size(); i++){
      delete ColorSpace[i];
  }
  // We init the 11 color for the diferents points
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
  }

  int j = 0;
  // We calculate the wich of the 11 colors is the nearest to the inertia centers
  switch(PointType){
  case 0:
  case 1:
  case 2:
  case 7:
      colors.resize(ColorSpace.size());
      for(int i = 0; i < v.size(); i++){
        j = getminordistance(v[i]);
        colors[j] += globalSet[i].getPoints().size();
      }
      break;
  case 3:
      colors = getFuzzyCIELAB(v, globalSet);
      break;
  case 8:
      colors = getFuzzyRGB(v);
      break;
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

  // Delete unused pointers
  cout << endl << "Deleting pointers " << "|";
  clock_t cl;
  cl = clock();
  for(int i = 0; i < globalSet.size(); i++){
    for(int j = 0; j < globalSet[i].getPoints().size(); j++){
        delete globalSet[i].getPoints()[j];
        switch((int)(((double)clock() - cl) / CLOCKS_PER_SEC)% 4){
        case 0:
            cout << "\b" << "/";
            break;
        case 1:
            cout << "\b" << "-";
            break;
        case 2:
            cout << "\b" << "\\";
            break;
        case 3:
            cout << "\b" << "|";
            break;
        }
    }
    cout << "\b" << (char) 219 << "|";
  }
  cout << endl;
  globalSet.clear();

  return output;
}

// Function to get in wich position is the minor distance
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
    km = Kmeans(getSet(PointType, Rep));
    try{
      globalSet = km.Calculate(k, Verbose);
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
