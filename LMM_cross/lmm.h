#ifndef LMM_H
#define LMM_H

#include "LedControl.h"

extern int LMS_DEV_X_NUM;
extern int LMS_DEV_Y_NUM;
extern int LMS_X_MAX;
extern int LMS_Y_MAX;

class Cross {
  public:
    int posX;
    int posY;
    Cross(int _x, int _y);
    void updatePos();
    void displayCrossA(LedControl lms[], int hl);
    void displayCrossB(LedControl lms[], int hl);
};

void initialize(LedControl lms[]);
void point(LedControl lms[], int x, int y, int hl) ;
void clearAllDisplay(LedControl lms[]) ;
void xAxisScanning(LedControl lms[], int delayTime);
void yAxisScanning(LedControl lms[], int delayTime) ;
void checkered(LedControl lms[], int delayTime);

#endif

