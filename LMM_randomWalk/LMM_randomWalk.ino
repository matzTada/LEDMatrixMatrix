#include "LedControl.h"
#include "lmm.h"

//(din, clock, load, #connected Led Matrix) in Arduino = (1, 12, 13) in MAX7219
LedControl lms[] = {
  LedControl(2, 4, 3, 4)
  ,
  LedControl(5, 7, 6, 4)
  //    ,
  //  LedControl(8, 10, 9, 4)
  //  ,
  //  LedControl(A0, A2, A1, 4)
};

int  LMS_DEV_X_NUM = lms[0].getDeviceCount();
int  LMS_DEV_Y_NUM = sizeof(lms) / sizeof(lms[0]);
int  LMS_X_MAX = 8 * LMS_DEV_X_NUM;
int  LMS_Y_MAX = 8 * LMS_DEV_Y_NUM;

void setup() {
  //  Serial.begin(9600);
  //  Serial.println(LMS_DEV_X_NUM );
  //  Serial.println(LMS_DEV_Y_NUM );

  initialize(lms);
}

void loop() {
  clearAllDisplay(lms);

  xAxisScanning(lms, 5);
  yAxisScanning(lms, 5);

  delay(100);
}

