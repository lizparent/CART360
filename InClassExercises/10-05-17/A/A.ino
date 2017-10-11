#include <Servo.h> 

#define SERVO_PIN 9
 
Servo servo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
int angle = 0;   // servo position in degrees 
 
void setup() 
{ 
  servo.attach(SERVO_PIN); 
} 
 
 
void loop() 
{ 
  // scan from 0 to 180 degrees
  for(angle = 0; angle < 180; angle++)  
  {                                  
    servo.write(angle); // wait for servo to reach pos               
    delay(15);                   
  } 
  // now scan back from 180 to 0 degrees
  for(angle = 180; angle > 0; angle--)    
  {                                
    servo.write(angle);  // wait for servo to reach pos          
    delay(15);       
  } 
} 
