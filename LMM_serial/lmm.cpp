#include "lmm.h"

Cross::Cross(int _x, int _y) {
  posX = _x;
  posY = _y;
}

void  Cross::updatePos() {
  posX += random(-1, 2);
  posY += random(-1, 2);
  posX = constrain(posX, 0, LMS_X_MAX - 1);
  posY = constrain(posY, 0, LMS_Y_MAX - 1);
}

void  Cross::displayCrossA(LedControl lms[], int hl) {
  for (int j = 0; j < LMS_X_MAX; j++) point(lms, posX, j, hl);
  for (int i = 0; i < LMS_Y_MAX; i++) point(lms, i, posY, hl);
}

void  Cross::displayCrossB(LedControl lms[], int hl) {
  int i, j;
  point(lms,posX, posY, hl);
  i = posX, j = posY;
  while (i >= 0 && j >= 0) {
    i--; j--;
    point(lms, i, j, hl);
  }
  i = posX, j = posY;
  while (i >= 0 && j < LMS_Y_MAX) {
    i--; j++;
    point(lms, i, j, hl);
  }
  i = posX, j = posY;
  while (i < LMS_X_MAX && j >= 0) {
    i++; j--;
    point(lms, i, j, hl);
  }
  i = posX, j = posY;
  while (i < LMS_X_MAX && j < LMS_Y_MAX) {
    i++; j++;
    point(lms, i, j, hl);
  }
}

void initialize(LedControl lms[]) {
  //Initialize Max 7219 LED Matrix
  for (int devY = 0; devY < LMS_DEV_Y_NUM; devY++) {
    for (int devX = 0; devX < LMS_DEV_X_NUM; devX++) {
      lms[devY].shutdown(devX, false); /* Set the brightness to a medium values */
      lms[devY].setIntensity(devX, 1);/* and clear the display */
      lms[devY].clearDisplay(devX);
    }
  }
}

void point(LedControl lms[], int x, int y, int hl) {
  //x
  int dev = 0;
  int col = 0;
  //y
  int num = 0;
  int row = 0;

  dev = x / 8;
  col = 7 - x % 8;
  num = y / 8;
  row = 7 - y % 8;

  lms[num].setLed(dev, row, col, hl);
}

void clearAllDisplay(LedControl lms[]) {
  for (int devY = 0; devY < LMS_DEV_Y_NUM; devY++)
    for (int devX = 0; devX < LMS_DEV_X_NUM; devX++)
      lms[devY].clearDisplay(devX);
}

void xAxisScanning(LedControl lms[], int delayTime) {
  for (int j = 0; j < LMS_Y_MAX; j++) {
    for (int i = 0; i < LMS_X_MAX; i++) {
      point(lms, i, j, HIGH);
      delay(delayTime);
      point(lms, i, j, LOW);
      delay(delayTime);
    }
  }
}

void yAxisScanning(LedControl lms[], int delayTime) {
  for (int i = 0; i < LMS_X_MAX; i++) {
    for (int j = 0; j < LMS_Y_MAX; j++) {
      point(lms, i, j, HIGH);
      delay(delayTime);
      point(lms, i, j, LOW);
      delay(delayTime);
    }
  }
}

void checkered(LedControl lms[], int delayTime) {
  for (int j = 0; j < LMS_Y_MAX; j++)
    for (int i = 0; i < LMS_X_MAX; i++)
      if ( (i + j) % 2 == 0) point(lms, i, j, HIGH);
  delay(delayTime);
  clearAllDisplay(lms);

  for (int j = 0; j < LMS_Y_MAX; j++)
    for (int i = 0; i < LMS_X_MAX; i++)
      if ( (i + j) % 2 == 1) point(lms, i, j, HIGH);
  delay(delayTime);
  clearAllDisplay(lms);
}
