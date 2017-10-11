#define LED_PIN 13

/****
   Timer variables
*/
unsigned long startTime; // variable to hold when we started the timer.
unsigned long timePassed; // variable to hold the value for
//how much time has passed since timer started
/* for 1st LED */
int onTime = 250;           // milliseconds of on-time interval
int offTime = 750;          // milliseconds of off-time interval
int ledState =LOW; // variable to holde state of LED

void setup() {
  pinMode(LED_PIN, OUTPUT);
  startTime = millis();


}

void loop() {

// calculate the new timePassed Var
  timePassed = millis() - startTime;
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
}

