
//#include "ShiftRegister.h"

int analogValue5, val5;
int tempPin = 5;
int val;
const char startNum = '<';
const char endNum = '>';
int current = 0;
int previous = 0;

void setup() {
// Serial port enable
Serial.begin(9600);
}

void loop() {
//// read analog pin 5
//analogValue5 = analogRead(A5);
//
//// remap values from the analogValue5 variable to 0 / 255
//val5 = map(analogValue5, 0, 1023, 0, 255);
//
//// send the value to the serial port
//Serial.println(val5);



val = analogRead(tempPin);
float mv = ( val/1024.0)*5000; 
current = mv/10;

if(current != previous) { 
//Serial.print("TEMPERATURE = ");
Serial.write(startNum);
Serial.write(current);
Serial.write(endNum);
//Serial.print("*C");
//Serial.write("\r\n");

delay(250);
previous = current;
}
//Serial.println(previous);
}
