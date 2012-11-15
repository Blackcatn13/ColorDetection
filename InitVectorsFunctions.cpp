#include "InitVectorsFunctions.h"

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
    vector<DPoint*> RGBDefactoColors = vector<DPoint*>();
    DPoint *p = new DPoint();
    vector<float> pos = vector<float>();
    // White
    pos.push_back(255); pos.push_back(255); pos.push_back(255);
    p->setPosition(pos);
    RGBDefactoColors.push_back(p);
    pos.clear();
    p = new DPoint();
    // Pink
    pos.push_back(255); pos.push_back(192); pos.push_back(203);
    p->setPosition(pos);
    RGBDefactoColors.push_back(p);
    pos.clear();
    p = new DPoint();
    // Red
    pos.push_back(255); pos.push_back(0); pos.push_back(0);
    p->setPosition(pos);
    RGBDefactoColors.push_back(p);
    pos.clear();
    p = new DPoint();
    // Orange
    pos.push_back(255); pos.push_back(127); pos.push_back(0);
    p->setPosition(pos);
    RGBDefactoColors.push_back(p);
    pos.clear();
    p = new DPoint();
    // Brown
    pos.push_back(150); pos.push_back(75); pos.push_back(0);
    p->setPosition(pos);
    RGBDefactoColors.push_back(p);
    pos.clear();
    p = new DPoint();
    // Yellow
    pos.push_back(255); pos.push_back(255); pos.push_back(0);
    p->setPosition(pos); 
    RGBDefactoColors.push_back(p);
    pos.clear();
    p = new DPoint();
    // Grey
    pos.push_back(128); pos.push_back(128); pos.push_back(128);
    p->setPosition(pos); 
    RGBDefactoColors.push_back(p);
    pos.clear();
    p = new DPoint();
    // Green
    pos.push_back(0); pos.push_back(255); pos.push_back(0);
    p->setPosition(pos);
    RGBDefactoColors.push_back(p);
    pos.clear();
    p = new DPoint();
    // Blue
    pos.push_back(0); pos.push_back(0); pos.push_back(255);
    p->setPosition(pos);
    RGBDefactoColors.push_back(p);
    pos.clear();
    p = new DPoint();
    // Purple
    pos.push_back(143); pos.push_back(0); pos.push_back(255);
    p->setPosition(pos);
    RGBDefactoColors.push_back(p);
    pos.clear();
    p = new DPoint();
    // Black
    pos.push_back(0); pos.push_back(0); pos.push_back(0);
    p->setPosition(pos);
    RGBDefactoColors.push_back(p);
    pos.clear();
    return vector<DPoint*>();
}

vector<DPoint*> initRGB(){
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
  pos.push_back(240);
  pos.push_back(240);
  pos.push_back(220);
  p->setPosition(pos);
  RGBAcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  // 1 - pink r = 255, g = 192, b = 203
  pos.push_back(220);
  pos.push_back(50);
  pos.push_back(220);
  p->setPosition(pos);
  RGBAcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //2 - red r = 255, g = 0, b = 0
    pos.push_back(220);
  pos.push_back(30);
  pos.push_back(30);
  p->setPosition(pos);
  RGBAcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //3 - orange r = 255, g = 127, b = 0
    pos.push_back(230);
  pos.push_back(130);
  pos.push_back(30);
  p->setPosition(pos);
  RGBAcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //4 - brown r = 150, g = 75, b = 0
    pos.push_back(130);
  pos.push_back(70);
  pos.push_back(30);
  p->setPosition(pos);
  RGBAcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //5 - yellow r = 255, g = 255, b = 0
  pos.push_back(220);
  pos.push_back(220);
  pos.push_back(30);
  p->setPosition(pos);
  RGBAcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //6 - grey  r = 128, g = 128, b = 128
    pos.push_back(120);
  pos.push_back(120);
  pos.push_back(120);
  p->setPosition(pos);
  RGBAcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //7 - green r = 0, g = 255, b = 0
  pos.push_back(30);
  pos.push_back(110);
  pos.push_back(30);
  p->setPosition(pos);
  RGBAcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //8 - blue r = 0, g = 0, b = 255
    pos.push_back(30);
  pos.push_back(30);
  pos.push_back(220);
  p->setPosition(pos);
  RGBAcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //9 - purple r = 143, g = 0, b = 255
    pos.push_back(180);
  pos.push_back(30);
  pos.push_back(200);
  p->setPosition(pos);
  RGBAcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  // 10- black r = 0, g = 0, b = 0
    pos.push_back(30);
  pos.push_back(30);
  pos.push_back(30);
  p->setPosition(pos);
  RGBAcolors.push_back(p);
  pos.erase(pos.begin(), pos.end());
  return RGBAcolors;
}

vector<DPoint*> initDefactoCIELAB(){
    
   // Defacto colors
  vector<DPoint*> labcolors = vector<DPoint*>();
  DPoint *p = new DPoint();
  vector<float> pos = vector<float>();
  //0 - white l = 100, a = 0, b = 0
  pos.push_back(100); pos.push_back(0); pos.push_back(0);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //1 - pink l = 92.069, a = 11.20, b = 1.05
  pos.push_back(92.069); pos.push_back(11.20); pos.push_back(1.05);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //2 - red l = 53.24, a = 80.09, a = 67.20
  pos.push_back(53.24); pos.push_back(80.09); pos.push_back(67.20);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //3 - orange l=80.11, a =12.36, b =82.4
  pos.push_back(80.11); pos.push_back(12.36); pos.push_back(82.4);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //    4 - brown l=64.59, a = 10.21, b=69.08
  pos.push_back(64.59); pos.push_back(10.21); pos.push_back(69.08);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //    5 - yellow l=97.139, a=-21.55, b=94.475
  pos.push_back(97.139); pos.push_back(-21.55); pos.push_back(94.475);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //    6 - grey  l=76.189, a = 0, b = 0
  pos.push_back(76.189); pos.push_back(0); pos.push_back(0);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //    7 - green l=87.73, a = -86.18, b=83.177
    pos.push_back(87.73);
  pos.push_back(-86.18);
  pos.push_back(83.177);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //    8 - blue l=32.29, a=79.18, b=-107.86
  pos.push_back(32.29); pos.push_back(79.18); pos.push_back(-107.86);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //    9 - purple l=50.85, a=90.15, b=-76.58
  pos.push_back(50.85); pos.push_back(90.15); pos.push_back(-76.58);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  //    10- black l=0, a=0, b=0
  pos.push_back(0); pos.push_back(0); pos.push_back(0);
  p->setPosition(pos);
  labcolors.push_back(p);
  pos.erase(pos.begin(), pos.end());

  return labcolors;
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
  // White
  pos.push_back(100); pos.push_back(0); pos.push_back(0);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  // Pink
  pos.push_back(89.745); pos.push_back(16.025); pos.push_back(-1.815);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  // Red
  pos.push_back(60.460); pos.push_back(59.572); pos.push_back(25.153);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  // Orange
  pos.push_back(85.732); pos.push_back(20.248); pos.push_back(53.706);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  // Brown
  pos.push_back(77.344); pos.push_back(9.679); pos.push_back(18.265);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  // Yellow
  pos.push_back(95.0); pos.push_back(-5.0); pos.push_back(30.0);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  // Grey
  pos.push_back(35.0); pos.push_back(0); pos.push_back(0);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  // Green
  pos.push_back(82.190); pos.push_back(-36.099); pos.push_back(29.940);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  // Blue
  pos.push_back(91.635); pos.push_back(-7.213); pos.push_back(-4.322);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  // Purple
  pos.push_back(44.498); pos.push_back(77.867); pos.push_back(-48.214);
  p->setPosition(pos);
  labcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  // Black
  pos.push_back(0); pos.push_back(0); pos.push_back(0);
  p->setPosition(pos);
  labcolors.push_back(p);
  pos.erase(pos.begin(), pos.end());

  return labcolors;
}

vector<DPoint*> initHSV(){
/*  0 - white   h = 0,      s = 0,    v = 1
    1 - pink    h = 349.52, s = 0.25, v = 1
    2 - red     h = 0,      s = 1,    v = 1
    3 - orange  h = 29.88,  s = 1,    v = 1
    4 - brown   h = 30,     s = 1,    v = 0.59
    5 - yellow  h = 60,     s = 1,    v = 1
    6 - grey    h = 0,      s = 0,    v = 0.5
    7 - green   h = 120,    s = 1,    v = 1
    8 - blue    h = 240,    s = 1,    v = 1
    9 - purple  h = 273.65, s = 1,    v = 1
    10- black   h = 0,      s = 0,    Sv = 0
*/
  vector<DPoint*> HSVcolors = vector<DPoint*>();
  DPoint *p = new DPoint();
  vector<float> pos = vector<float>();
  // White
  pos.push_back(0); pos.push_back(0); pos.push_back(1);
  p->setPosition(pos);
  HSVcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  // Pink
  pos.push_back(349.52); pos.push_back(0.25); pos.push_back(1);
  p->setPosition(pos);
  HSVcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  // Red
  pos.push_back(0); pos.push_back(1); pos.push_back(1);
  p->setPosition(pos);
  HSVcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  // Orange
  pos.push_back(29.88); pos.push_back(1); pos.push_back(1);
  p->setPosition(pos);
  HSVcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  // Brown
  pos.push_back(30); pos.push_back(1); pos.push_back(0.59);
  p->setPosition(pos);
  HSVcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  // Yellow
  pos.push_back(60); pos.push_back(1); pos.push_back(1);
  p->setPosition(pos);
  HSVcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  // Grey
  pos.push_back(0); pos.push_back(0); pos.push_back(0.5);
  p->setPosition(pos);
  HSVcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  // Green
  pos.push_back(120); pos.push_back(1); pos.push_back(1);
  p->setPosition(pos);
  HSVcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  // Blue
  pos.push_back(240); pos.push_back(1); pos.push_back(1);
  p->setPosition(pos);
  HSVcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  // Purple
  pos.push_back(273.65); pos.push_back(1); pos.push_back(1);
  p->setPosition(pos);
  HSVcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
  // Black
  pos.push_back(0); pos.push_back(0); pos.push_back(0);
  p->setPosition(pos);
  HSVcolors.push_back(p);
  p = new DPoint();
  pos.erase(pos.begin(), pos.end());
}
