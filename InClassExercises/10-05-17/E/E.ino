// These variables store the flash pattern
// and the current state of the LED

#define LED_PIN 13
// second LED
#define LED_PIN_2 12

int ledState = LOW;             // ledState used to set the LED
unsigned long startTime; // variable to hold when we started the timer.
unsigned long timePassed; // variable to hold the value for
//how much time has passed since timer started

/* for 1st LED */
int onTime = 250;           // milliseconds of on-time interval
int offTime = 750;          // milliseconds of off-time interval

/* for 2nd LED */

unsigned long startTime_2; // variable to hold when we started the timer.
unsigned long  timePassed_2; // variable to hold the value for
//how much time has passed since timer started


int ledState_2 = LOW;             // ledState used to set the LED
int onTime_2 = 330;           // milliseconds of on-time
int offTime_2 = 400;          // milliseconds of off-time
 

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  // initialize the startTime variable
  startTime = millis();
  startTime_2 = millis();
}

void loop()
{
  // calculate the new timePassed Var
  timePassed = millis() - startTime;

   timePassed_2 = millis() - startTime_2;

  if ((ledState == HIGH) && (timePassed >= onTime))
  {
    ledState = LOW;  // Turn it off
    startTime = millis();
    timePassed = 0;
    digitalWrite(LED_PIN, ledState);  // Update the actual LED
  }
  else if ((ledState == LOW) && (timePassed >= offTime))
  {
    ledState = HIGH;  // turn it on
    startTime = millis();
    timePassed = 0;
    digitalWrite(LED_PIN, ledState);    // Update the actual LED
  }

// for 2ND LED
   if ((ledState_2 == HIGH) && (timePassed_2 >= onTime_2))
  {
    ledState_2 = LOW;  // Turn it off
    startTime_2 = millis();
    timePassed_2 = 0;
    digitalWrite(LED_PIN_2, ledState_2);  // Update the actual LED
  }
  else if ((ledState_2 == LOW) && (timePassed_2 >= offTime_2))
  {
    ledState_2 = HIGH;  // turn it on
    startTime_2 = millis();
    timePassed_2 = 0;
    digitalWrite(LED_PIN_2, ledState_2);    // Update the actual LED
  }
}
