#include <Servo.h>

Servo myservo;  
Servo myservo2; 
//tower servo 
int motor;
// not tower servo
int motor2;

  #define trigPin 7
#define echoPin 2
   

void setup() {
  //tower servo right side
  myservo.attach(10); 
  //not tower servo left side
  myservo2.attach(9); 
 
  motor = 0;
  motor2=180;
  

  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //default to 0 degrees
  myservo.write(motor);
  //default it to 180 degrees
    myservo2.write(motor2);

  
}




void loop() {




  float duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0344;
  
    if(distance <=50){
      
    myservo.write(90);
    myservo2.write(90);

  } else if (distance>=51){
    myservo.write(motor);
    myservo2.write(motor2);

  

    
  }

}
