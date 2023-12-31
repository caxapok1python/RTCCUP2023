// MEGA2560 PINS ONLY
// Buttons
#define LEFT_BUTTON A7
//#define RIGHT_BUTTON A9

// Tumblers
#define LOW_TUMBLER A8
#define MIDDLE_TUMBLER A9
#define HIGH_TUMBLER A5
#define MODE_TUMBLER A3

// Sticks
#define LEFT_STICK A2
#define RIGHT_STICK A4

// constant joystick ranges
const int stickRange[3] = {971, 1979, 1475}; // stick range (min, max, medium)
const int centerRange = 60; // anti noise protection in medium position of stick
const int tumblerRange[3] = {1200, 1800}; // tumbler range (min deadline, max deadline)
const int buttonRange = 1500; // button deadpoint

// setup start position of sticks
short int leftStick = 0;
short int rightStick = stickRange[2];

// setup start position of tumblers
short int lowTumbler, midTumbler, highTumbler, modeTumbler = tumblerRange[2];

// setup default button position
bool buttonLeft = false;


// setup
// setup joysick pins
void setupJoystick(){
  pinMode(LEFT_STICK, INPUT);
  pinMode(RIGHT_STICK, INPUT);
  pinMode(LOW_TUMBLER, INPUT);
  pinMode(MIDDLE_TUMBLER, INPUT);
  pinMode(HIGH_TUMBLER, INPUT);
  pinMode(MODE_TUMBLER, INPUT);
  pinMode(LEFT_BUTTON, INPUT);
}


// loop
// read sticks
void readSticks(){
  leftStick = pulseIn(LEFT_STICK, 1);
  rightStick = pulseIn(RIGHT_STICK, 1);
}

// read tumblers
void readMode(){
  modeTumbler = pulseIn(MODE_TUMBLER, 1);
}
void readLow(){
  lowTumbler = pulseIn(LOW_TUMBLER, 1);
}
void readMid(){
  midTumbler = pulseIn(MIDDLE_TUMBLER, 1);
}
void readHigh(){
  highTumbler = pulseIn(HIGH_TUMBLER, 1);
}
void readTumblers(){ // all
  lowTumbler = pulseIn(LOW_TUMBLER, 1);
  midTumbler = pulseIn(MIDDLE_TUMBLER, 1);
  highTumbler = pulseIn(HIGH_TUMBLER, 1);
  modeTumbler = pulseIn(MODE_TUMBLER, 1);
}

// read button
void readJoyButton(){
  if (pulseIn(LEFT_BUTTON, 1) > buttonRange) buttonLeft = true;
  else buttonLeft = false;
}


// debug
//
void debugJoystick(){
  Serial.print("A0:");
  Serial.print(pulseIn(A0, 1));
  Serial.print(" | ");

  Serial.print("A1:");
  Serial.print(pulseIn(A1, 1));
  Serial.print(" | ");

  Serial.print("A2:");
  Serial.print(pulseIn(A2, 1));
  Serial.print(" | ");

  Serial.print("A3:");
  Serial.print(pulseIn(A3, 1));
  Serial.print(" | ");

  Serial.print("A4:");
  Serial.print(pulseIn(A4, 1));
  Serial.print(" | ");

  Serial.print("A5:");
  Serial.print(pulseIn(A5, 1));
  Serial.print(" | ");

  Serial.print("A6:");
  Serial.print(pulseIn(A6, 1));
  Serial.print(" | ");

  Serial.print("A7:");
  Serial.print(pulseIn(A7, 1));
  Serial.print(" | ");

  Serial.print("A8:");
  Serial.print(pulseIn(A8, 1));
  Serial.print(" | ");

  Serial.print("A9:");
  Serial.print(pulseIn(A9, 1));
  Serial.print(" | ");

  // Serial.print("A10:");
  // Serial.print(analogRead(A10));
  // Serial.print(" | ");

  // Serial.print("A11:");
  // Serial.print(analogRead(A11));
  // Serial.print(" | ");

  Serial.println();
}

// calibrate sticks max and min
void calibateSticks(){
  // start
  short int lmin = 2000;
  short int rmin = 2000;
  short int lmax = 0;
  short int rmax = 0;

  while (true){
    readSticks();
    lmin = min(lmin, leftStick);
    rmin = min(rmin, rightStick);
    lmax = max(lmax, leftStick);
    rmax = max(rmax, rightStick);
    Serial.print(lmin);
    Serial.print("-");
    Serial.print(lmax);
    Serial.print(" ");
    Serial.print(rmin);
    Serial.print("-");
    Serial.print(rmax);
    Serial.println();
    delay(100);
  }
}


