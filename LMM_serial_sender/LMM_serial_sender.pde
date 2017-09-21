/**
 * Many Serial Ports
 * 
 * Read data from the multiple Serial Ports
 */


import processing.serial.*;

Serial[] myPorts = new Serial[2];  // Create a list of objects from Serial class

int LMM_WIDTH = 32;
int LMM_HEIGHT = 32;

boolean[][] lmmArray = new boolean [LMM_WIDTH][LMM_HEIGHT];

void setup() {
  size(800, 800);
  frame.setResizable(true);
  // print a list of the serial ports:
  printArray(Serial.list());
  // On my machine, the first and third ports in the list
  // were the serial ports that my microcontrollers were 
  // attached to.
  // Open whatever ports ares the ones you're using.

  // get the ports' names:
  //String portOne = Serial.list()[0];
  //String portTwo = Serial.list()[1];
  String portOne = "COM18";
  String portTwo = "COM14";
  // open the ports:
  myPorts[0] = new Serial(this, portOne, 9600);
  myPorts[1] = new Serial(this, portTwo, 9600);
}


int boxWidth = width / LMM_WIDTH;
int boxHeight = height / LMM_HEIGHT;

void draw() {
  // clear the screen:
  background(0);
  boxWidth = width / LMM_WIDTH;
  boxHeight = height / LMM_HEIGHT;

  for (int j = 0; j < LMM_HEIGHT; j++) {
    for (int i = 0; i < LMM_HEIGHT; i++) {
      stroke(127);
      if (lmmArray[i][j] == true) {
        fill(255);
      } else {
        fill(0);
      }
      rect(i * boxWidth, j *boxHeight, boxWidth, boxHeight);
    }
  }
}

/** 
 * When SerialEvent is generated, it'll also give you
 * the port that generated it.  Check that against a list
 * of the ports you know you opened to find out where
 * the data came from
 */
void serialEvent(Serial thisPort) {
  // variable to hold the number of the port:
  int portNumber = -1;

  // iterate over the list of ports opened, and match the 
  // one that generated this event:
  for (int p = 0; p < myPorts.length; p++) {
    if (thisPort == myPorts[p]) {
      portNumber = p;
    }
  }
  // read a byte from the port:
  int inByte = thisPort.read();
  if ('a' < inByte && inByte < 'z' || 'A' < inByte && inByte < 'Z') {
    // tell us who sent what:
    print(portNumber + " " + char(inByte) + " ");
  }
}

void mouseDragged() {
  int x = mouseX / boxWidth;
  int y = mouseY / boxHeight;
  x = constrain(x, 0, LMM_WIDTH - 1);
  y = constrain(y, 0, LMM_HEIGHT - 1);
  if (mouseButton==LEFT) {
    lmmArray[x][y] = true;
  } else {
    lmmArray[x][y] = false;
  }
}

void keyPressed() {
  switch (key) {
  case 'n':
    println("---");
    println("start sending");
    println("---");
    for (int i = 0; i < LMM_HEIGHT; i++) {
      String sendStr = "n";
      if (i< 16) {
        sendStr += char(i + int('0'));
      } else {
        sendStr += char(i - 16 + int('0'));
      }
      for (int j = 0; j < LMM_WIDTH; j++) {
        sendStr += (lmmArray[j][i]) ? "1" : "0";
      }
      sendStr += "\n";

      if (i < 16) {
        for (int k = 0; k < sendStr.length(); k++) {
          myPorts[0].write(sendStr.charAt(k));
        }
      } else {      
        for (int k = 0; k < sendStr.length(); k++) {
          myPorts[1].write(sendStr.charAt(k));
        }
      }
      print("wrote:" + i + " " + sendStr);
      delay(100);

      //String sendStr = "n011110000111100001111000011110000\n";
      //for (int i = 0; i < sendStr.length(); i++) {
      //  myPorts[0].write(sendStr.charAt(i));
      //  myPorts[1].write(sendStr.charAt(i));
      //  delay(200);
      //}
    }
    println("---");
    println("finish sending");
    println("---");
    refreshDisplay();
    break;
  case 'r':
    resetArray();
    break;
  case 'c':
  case 'o':
  case 'f':
  case 'x':
  case 'y':
    sendCommand(key);
    break;
  default:
    break;
  }
}

void sendCommand(char chr) {
  myPorts[0].write(chr);
  myPorts[0].write('\n');
  myPorts[1].write(chr);
  myPorts[1].write('\n');
}

void refreshDisplay() {
  sendCommand('f');
  sendCommand('o');
}

void resetArray() {
  for (int j = 0; j < LMM_HEIGHT; j++) {
    for (int i = 0; i < LMM_HEIGHT; i++) {
      lmmArray[i][j] = false;
    }
  }
}