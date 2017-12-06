#include <Servo.h>

#define SERVO_PIN_1 9
#define SERVO_PIN_2 10
#define SERVO_PIN_3 11

int currentId = 0;
byte incomingByte;

Servo myservo1;
Servo myservo2;
Servo myservo3;

void setup() {
  // initialize the button pin as an input:

  // initialize serial communication:
  Serial.begin(9600);
  myservo1.attach(SERVO_PIN_1);  
  myservo2.attach(SERVO_PIN_2);
  myservo3.attach(SERVO_PIN_3);
}


void loop() {
  while (Serial.available() > 0)
  {

    incomingByte = Serial.read(); // read it

    if (incomingByte == 'A' ) {


      while (currentId < 1) {
        delay(10);
        incomingByte = Serial.read();
        myservo1.write(incomingByte);
        currentId++;
      }
    }

    else if (incomingByte == 'B' ) {


      while (currentId < 1) {
        delay(10);
        incomingByte = Serial.read();
        myservo2.write(incomingByte);
         currentId++;
        //analogWrite(LED,incomingByte);

      }
    }

    else if (incomingByte == 'C' ) {


      while (currentId < 1) {
       delay(10);
        incomingByte = Serial.read();
         currentId++;
        myservo3.write(incomingByte);
        //analogWrite(LED,incomingByte);

      }
    }
    currentId = 0;


  }

}









