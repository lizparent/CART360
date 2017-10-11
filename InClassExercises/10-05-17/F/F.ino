#include <Servo.h> 

#define SERVO_PIN 9

Servo servo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
 
int pos = 0;    // variable to store the servo position 

int increment =1; // how much should servo move each time?

// timer vars
unsigned long startTime;
unsigned long timePassed;
int interval =15;

 
void setup() 
{ 
  servo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object 
  startTime =millis();
} 
 
void loop() 
{ 
  // calculate time
  timePassed = millis() - startTime;
   if(timePassed > interval)  // time to update
    {
      // reset timer
      startTime =millis();
      timePassed =0;

      // change servo position
      pos += increment;
      servo.write(pos);

      // check if we should go in another direction
      if ((pos >= 180) || (pos <= 0)) // end of sweep
      {
        // reverse direction
        increment = -increment;
      }
    }
} 
