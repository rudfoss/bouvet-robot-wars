/* This example uses the Zumo32U4PrimeBuzzer class to play a
series of notes on the buzzer.

This example demonstrates the use of the playFrequency(),
playNote().

This example also shows how to use the stopPlaying() function to
stop the buzzer, and it shows how to use the isPlaying() function
to tell whether the buzzer is still playing or not. */

#include <Arduino.h>
#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Buzzer buzzer;

void setup()
{
}

void loop() 
{
  /* 1. Start playing a tone with frequency 440 Hz at maximum
   volume (15) for 200 milliseconds.*/
  // buzzer.playFrequency(440, 200, 15);
  // while(buzzer.isPlaying());
  

  /* 2. Delay to give the tone time to finish. Delay with 1000 ms */

  /* 3. Start playing note A in octave 4 at maximum volume
   volume (15) for 2000 milliseconds.*/
  // buzzer.playNote('A', 2000, 15);
  delay(2000);
  buzzer.stopPlaying();

  /* 4. Wait for 200 ms and stop playing note.*/

  


  // delay(50);
}
