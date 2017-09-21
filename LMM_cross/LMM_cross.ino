#include "LedControl.h"
#include "lmm.h"

//(din, clock, load, #connected Led Matrix) in Arduino = (1, 12, 13) in MAX7219
LedControl lms[] = {LedControl(2, 4, 3, 4),
                    LedControl(5, 7, 6, 4)
//                    ,
//                    LedControl(8, 10, 9, 4),
//                    LedControl(A0, A2, A1, 4)
                   };

int  LMS_DEV_X_NUM = lms[0].getDeviceCount();
int  LMS_DEV_Y_NUM = sizeof(lms) / sizeof(lms[0]);
int  LMS_X_MAX = 8 * LMS_DEV_X_NUM;
int  LMS_Y_MAX = 8 * LMS_DEV_Y_NUM;

Cross crs[] = {
  Cross(random(0, LMS_X_MAX), random(0, LMS_Y_MAX)),
  Cross(random(0, LMS_X_MAX), random(0, LMS_Y_MAX)),
  Cross(random(0, LMS_X_MAX), random(0, LMS_Y_MAX)),
  Cross(random(0, LMS_X_MAX), random(0, LMS_Y_MAX))
};

void setup() {
  initialize(lms);
  checkered(lms, 10);
  xAxisScanning(lms, 1);
  yAxisScanning(lms, 1);
}

void loop() {
  for (int cr = 0; cr < sizeof(crs) / sizeof(crs[0]); cr++) crs[cr].updatePos();
//  for (int cr = 0; cr < sizeof(crs) / sizeof(crs[0]); cr++) crs[cr].displayCrossA(lms, HIGH);
  for (int cr = 0; cr < sizeof(crs) / sizeof(crs[0]); cr++) crs[cr].displayCrossB(lms, HIGH);
  delay(10);
  clearAllDisplay(lms);
}

