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

int LMS_DEV_X_NUM = (int)lms[0].getDeviceCount();
int LMS_DEV_Y_NUM = (int)sizeof(lms) / sizeof(lms[0]);
int LMS_X_MAX = 8 * LMS_DEV_X_NUM;
int LMS_Y_MAX = 8 * LMS_DEV_Y_NUM;

byte* lmsArray; //pointer for array

void setup() {
  Serial.begin(9600);
  Serial.println(LMS_DEV_X_NUM );
  Serial.println(LMS_X_MAX);
  Serial.println(LMS_DEV_Y_NUM );
  Serial.println(LMS_Y_MAX);

  initialize(lms);

  //array handling
  lmsArray = new byte[LMS_DEV_X_NUM * LMS_DEV_Y_NUM * 8];
  clearArray();

  //  lmsArray[0] = 255;
  //  lmsArray[1] = 255;
  //  lmsArray[2] = 255;
  //  lmsArray[3] = 255;
  //  lmsArray[32] = 255;
}

void loop() {
  if (Serial.available() > 0) {
    int ypos = 0;
    String rstr = Serial.readStringUntil('\n');
    char fc = rstr.charAt(0);
    switch (fc) {
      case 'n': // impose new str
        ypos = (int)(rstr.charAt(1) - '0');
        for (int i = 0; i < 4; i++) {
          byte tb = 0;
          for (int j = 0; j < 8; j++) {
            if (rstr.charAt(2 + i * 8 + j) - '0' == 1) {
              tb += bit(7 - j);
            }
          }
          lmsArray[i + ypos * 4] = tb;
        }
        break;
      case 'c':
        clearArray();
        break;
      case 'o':
        switchOn();
        break;
      case 'f':
        clearAllDisplay(lms);
        break;
      case 'x':
        xAxisScanning(lms, 5);
        break;
      case 'y':
        yAxisScanning(lms, 5);
        break;
      default:
        break;
    }
    Serial.println(rstr);
  }
}


void clearArray() {
  for (int i = 0; i < LMS_DEV_X_NUM * LMS_DEV_Y_NUM * 8; i++) {
    lmsArray[i] = 0;
  }
}

void switchOn() { //switch on
  for (int i = 0; i < LMS_DEV_X_NUM * LMS_DEV_Y_NUM * 8; i++) {
    int y = i / LMS_DEV_X_NUM;
    int x = i % 4;
    for (int j = 0; j < 8; j++) {
      byte tb = 1;
      if (lmsArray[i] & (tb << (7 - j))) {
        point(lms, x * 8 + j, y, HIGH);
      }
    }
  }
}
