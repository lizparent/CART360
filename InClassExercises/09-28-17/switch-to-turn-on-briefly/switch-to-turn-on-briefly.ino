#define LED_PIN 11
#define BUTTON_PIN 2

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
  if(buttonVal == HIGH)
  {
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  delay(1000);
  }
}
