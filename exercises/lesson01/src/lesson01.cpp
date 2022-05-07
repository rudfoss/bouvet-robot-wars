/* This lesson will teach you how to interface with
the pushbuttons on the Zumo.*/

#include <Arduino.h>
#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4ButtonB buttonB;
Zumo32U4LCD lcd;

void setup()
{
  lcd.clear();
  lcd.print(F("Press b"));

  /* 1. Use the waitForButton() function, which blocks and
   * doesn't return until a button press and release are
   * detected. */
  buttonB.waitForButton();
  lcd.clear();
}

void loop()
{
  /* 2. Directly read the state of the button with the
   * isPressed() function. */
  if (buttonB.isPressed()) {
    lcd.print(F("down"));
    lcd.clear();
  } else {
    lcd.print(F("up"));
    lcd.clear();
  }
  // lcd.print(F("go"));

  // buttonB.waitForButton();
  // i++;
  // lcd.clear();
}
