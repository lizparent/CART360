#define LED_PIN 11
#define BUTTON_PIN 2
boolean buttonState = false;
boolean prevButtonState = true;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  //Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonVal = digitalRead(BUTTON_PIN);
  //Serial.println(buttonVal);
  if (buttonVal == HIGH)
  {
    if (buttonState != prevButtonState) {
      buttonState = ! buttonState;
      prevButtonState = buttonState;
    }
    delay(200);
  }
  else{
    prevButtonState = !buttonState;
    }

  if (buttonState == true)
  {
    digitalWrite(LED_PIN, HIGH);
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
  }
}
