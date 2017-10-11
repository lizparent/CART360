#define LED_PIN 13
#define POT_PIN A0

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int pinVal = analogRead(POT_PIN);
  Serial.println(pinVal);
  digitalWrite(LED_PIN, HIGH);
  delay(pinVal);
  digitalWrite(LED_PIN, LOW);
  delay(pinVal);
}
