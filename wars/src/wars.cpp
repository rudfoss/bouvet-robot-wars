/**
  Mechanic Automated Garbage Disposal Android
  MAGDA
**/

/** This example uses the Zumo's line sensors to detect the black
border around a sumo ring.  When the border is detected, it
backs up and turns. */

#include <Arduino.h>
#include <Wire.h>
#include <Zumo32U4.h>

// This might need to be tuned for different lighting conditions,
// surfaces, etc.
#define QTR_THRESHOLD     1000  // microseconds

// These might need to be tuned for different motor types.
// alle hastigheter økt med 50 for test
#define REVERSE_SPEED     250  // 0 is stopped, 400 is full speed
#define TURN_SPEED        250  
#define FORWARD_SPEED     250 
#define ATTACK_SPEED      300
#define REVERSE_DURATION  200  // ms
#define TURN_DURATION     300  // ms
#define STARTING_TURN_DURATION  400  // ms


Zumo32U4LCD lcd;
Zumo32U4ButtonB buttonB;
Zumo32U4Buzzer buzzer;
Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;
Zumo32U4ProximitySensors proxSensors;

#define NUM_SENSORS 3
unsigned int lineSensorValues[NUM_SENSORS];
int frontLeftProx;
int frontRightProx;
int lrProx;
int llProx;
int rlProx;
int rrProx;

void waitForButtonAndCountDown()
{
  ledYellow(1);
  lcd.clear();
  lcd.print(F("Ready?"));

  while (!buttonB.isPressed()){
    lcd.gotoXY(0, 1);
    lcd.print(String(float(readBatteryMillivolts())/1000) + "V");
  }

  ledYellow(0);
  lcd.clear();

  // Play audible countdown. Darth Vader edition
  buzzer.playNote(NOTE_A(4), 450, 15); 
  delay(500);
  buzzer.playNote(NOTE_A(4), 450, 15); 
  delay(500);    
  buzzer.playNote(NOTE_A(4), 450, 15);
  delay(500);

  buzzer.playNote(NOTE_F(4), 300, 15); 
  delay(350);
  buzzer.playNote(NOTE_C(5), 100, 15);
  delay(150); ;
  buzzer.playNote(NOTE_A(4), 450, 15);
  delay(500);

  buzzer.playNote(NOTE_F(4), 300, 15);
  delay(350);
  buzzer.playNote(NOTE_C(5), 100, 15);
  delay(150);
  buzzer.playNote(NOTE_A(4), 2000, 15);
  delay(2000);
  
  lcd.print(F("GO MAGDA!"));
  ledRed(1);
}

void turnAndCharge()
{
  // rygger litt
  motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
  delay(REVERSE_DURATION);
  motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
}

void setup()
{
  lineSensors.initThreeSensors();
  proxSensors.initThreeSensors();
  waitForButtonAndCountDown();
  turnAndCharge();
}

void readProxSensors() {
  proxSensors.read();
  frontLeftProx = proxSensors.countsFrontWithLeftLeds(); // Forward facing left
  frontRightProx = proxSensors.countsFrontWithRightLeds(); // Forward facing right
  lrProx = proxSensors.countsLeftWithRightLeds(); // Left side facing forward
  llProx = proxSensors.countsLeftWithLeftLeds(); // Left side facing back
  rlProx = proxSensors.countsRightWithLeftLeds(); // Right side facing forward
  rrProx = proxSensors.countsRightWithRightLeds(); // Right side facing back

  lcd.clear();
  lcd.print(frontLeftProx);
  lcd.gotoXY(2,0);
  lcd.print(frontRightProx);
  lcd.gotoXY(4,0);
  lcd.print(lrProx);
  lcd.gotoXY(6,0);
  lcd.print(llProx);
  lcd.gotoXY(0,1);
  lcd.print(rlProx);
  lcd.gotoXY(0,1);
  lcd.print(rrProx);
  lcd.gotoXY(0,3);
}

void avoidEdge() {
  if (lineSensorValues[0] > QTR_THRESHOLD) //flip aligator sign if you want to detect white edges on a black board instead of black border on a white board.
  {
    // If leftmost sensor detects line, reverse and turn to the
    // right.
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);

    /* 7. Add three code lines for setting turn speed to turn right (+/- TURN_SPEED),
     *  add turn duration delay and then continuing forward.
     */
    motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    delay(TURN_DURATION);
  }
  else if (lineSensorValues[NUM_SENSORS - 1] > QTR_THRESHOLD) //flip aligator sign if you want to detect white edges on a black board instead of black border on a white board.
  {
    /* 8.  If rightmost sensor detects line, reverse and turn to the
     left. */

    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);

    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    delay(TURN_DURATION);
  }
}


void loop()
{
  if (buttonB.isPressed())
  {
    // If button is pressed, stop and wait for another press to
    // go again.
    motors.setSpeeds(0, 0);
    buttonB.waitForRelease();
    waitForButtonAndCountDown();
  }
  
  lineSensors.read(lineSensorValues);
  readProxSensors();
  avoidEdge();

  if (frontLeftProx > 2 || frontRightProx > 2) {
    motors.setSpeeds(ATTACK_SPEED, ATTACK_SPEED);
    return;
  }

  if (lrProx > 3 || rlProx > 3 || rlProx > 3 || rrProx > 3) {
    motors.setSpeeds(ATTACK_SPEED, ATTACK_SPEED);
    delay(500);
    return;
  }

  delay(200);
  motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
}
