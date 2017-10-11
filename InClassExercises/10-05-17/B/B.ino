#include <Servo.h> 

#define LED_PIN 13
#define SERVO_PIN 9

Servo myservo;  
int angle = 0;    // variable to store the servo position 
 
void setup() 
{ 
  // initialize the digital pin as an output.
  pinMode(LED_PIN, OUTPUT);     
  myservo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object 
} 
 
void loop() 
{ 
  digitalWrite(LED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(LED_PIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second

  // scan from 0 to 180 degrees
  for(angle = 0; angle <= 180; angle += 1) 
  {                              
    myservo.write(angle);            
    delay(15);  // wait for servo to reach pos                    
  }
  // now scan back from 180 to 0 degrees 
  for(angle = 180; angle>=0; angle-=1)    
  {                                
    myservo.write(angle);             
    delay(15);  // wait for servo to reach pos                      
  } 
} 
