#define LED_PIN 13

/****
   Timer variables
*/
unsigned long startTime; // variable to hold when we started the timer.
unsigned long timePassed; // variable to hold the value for
//how much time has passed since timer started
int interval = 1000; // when the timer expires
int ledState =LOW; // variable to holde state of LED

void setup() {
  pinMode(LED_PIN, OUTPUT);
  // initialize the startTime variable
  startTime = millis();


}

void loop() {

// calculate the new timePassed Var
  timePassed = millis() - startTime;
// condition to check if timePassed is > interval var
  if (timePassed > interval)
  {
    // switch the led state var
    if (ledState == HIGH)
      ledState = LOW;
    else
      ledState = HIGH;

    // reset the timer
    startTime = millis();
    timePassed = 0;
  }
  // do the correct action
  digitalWrite(LED_PIN,ledState);
}



