#include <Servo.h>

#define LED_PIN 13
// second LED
#define LED_PIN_2 12

#define SERVO_PIN 9
#define SERVO_PIN_2 11

#define BUTTON_PIN 2

// Lets make a Timer Class
class Timer
{

    unsigned long startTime;
    unsigned long timePassed;
    unsigned int onTime;
    unsigned int offTime;

  public:
    Timer(int on, int off)
    {
      onTime = on;
      offTime = off;
    }

    void setUp()
    {
      startTime = millis();
      //Serial.println(onTime);
    }
    // general function to update the time passed
    void updateTimer()
    {
      timePassed = millis() - startTime;
      //Serial.println(timePassed);
    }
    // general function to check if we have passed the first interval
    boolean passedIntervalOne()
    {
      //Serial.println(timePassed);

      if (timePassed > onTime)
      {
        startTime = millis();
        timePassed = 0;
        // Serial.println(onTime);
        return true;
      }
      return false;
    }
    // general function to check if we have passed the second interval
    boolean passedIntervalTwo()
    {
      if (timePassed > offTime)
      {
        startTime = millis();
        timePassed = 0;
        return true;
      }
      return false;
    }
};


/*make 2 instances of the timer class  - 1 for each LED //automatic
  You should use new when you wish an object to remain in existence until you delete it.
  If you do not use new then the object will be destroyed when it goes out of scope.

*/
Timer timerForLED_1(100, 400);
Timer timerForLED_2(350, 350);
int ledState_1 = LOW;
int ledState_2 = LOW;


// make an instance of servo class
Servo servo;

Servo servo2;

int position_1 = 0;
int speed_1 = 1;

int position_2 = 0;
int speed_2 = 1;

Timer timerForMotor_1(5, 0);
Timer timerForMotor_2(5, 0);


void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);

  servo.attach(SERVO_PIN); // reference pin with Servo obj
  servo2.attach(SERVO_PIN_2); // reference pin with Servo obj
  Serial.begin(9600);
  timerForMotor_1.setUp();
  timerForMotor_2.setUp();
  timerForLED_1.setUp();
  timerForLED_2.setUp();

}

void loop() {

  // call methods from the class to update timer associated with each component
  timerForLED_1.updateTimer();
  timerForLED_2.updateTimer();
  timerForMotor_1.updateTimer();
  timerForMotor_2.updateTimer();

  runStateMachineForLED(timerForLED_1, ledState_1, LED_PIN);
  runStateMachineForLED(timerForLED_2, ledState_2, LED_PIN_2);
  runStateMachineForMOTOR(servo, timerForMotor_1, speed_1, position_1);
  
  if(digitalRead(BUTTON_PIN) ==HIGH)
  {
  runStateMachineForMOTOR(servo2,timerForMotor_2, speed_2, position_2);
  }
 

}

// function for state machine for LEDS
void runStateMachineForLED(Timer & t, int & lState , int pinNum)
{

  if ((lState == HIGH) && (t.passedIntervalOne()))
  {
    lState = LOW;  // Turn it off
    digitalWrite(pinNum, lState);  // Update the actual LED
  }
  else if ((lState == LOW) && (t.passedIntervalTwo()))
  {
    lState = HIGH; // turn it on
    digitalWrite(pinNum, lState);    // Update the actual LED
  }
}

// function for state machines for motor
// pass by reference
void runStateMachineForMOTOR(Servo & sTemp, Timer & t, int &inc, int &pos)
{

  if (t.passedIntervalOne()) // time to update
  {
    pos += inc;
    sTemp.write(pos);

    if ((pos >= 180) || (pos <= 0)) // end of sweep
    {
      // reverse direction
      inc = -inc;
    }

  }
}

