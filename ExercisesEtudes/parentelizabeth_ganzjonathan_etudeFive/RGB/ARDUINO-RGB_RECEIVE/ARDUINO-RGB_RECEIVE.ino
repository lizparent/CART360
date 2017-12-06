#define LED 3
#define COLOR_PIN 6

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
byte incomingByte = 255;
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      8

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, COLOR_PIN, NEO_GRB + NEO_KHZ800);

int r, g, b;
int currentId = 0;

void setup() {
  // initialize the button pin as an input:

  // initialize serial communication:
  Serial.begin(9600);
  pixels.begin(); // This initializes the NeoPixel library.

}


void loop() {
  while (Serial.available() > 0)
  {
    incomingByte = Serial.read(); // read it
    
      if (incomingByte == 'A' ) {
        int colours[3] = {0};
        
        while(currentId < 3) {
          delay(100);
          colours[currentId++] = Serial.read();
          }
        
  
          pixels.setPixelColor(0, pixels.Color(colours[0], colours[1], colours[2])); // Moderately bright green color.
          pixels.show(); // This sends the updated pixel color to the hardware.
          delay(1000);
          pixels.setPixelColor(0, pixels.Color(0, 0, 0));
          pixels.show();
        }

        else if (incomingByte == 'B' ) {
        int colours[3] = {0};
        
        while(currentId < 3) {
          delay(100);
          colours[currentId++] = Serial.read();
          }
        
  
          pixels.setPixelColor(1, pixels.Color(colours[0], colours[1], colours[2])); // Moderately bright green color.
          pixels.show(); // This sends the updated pixel color to the hardware.
          delay(1000);
          pixels.setPixelColor(1, pixels.Color(0, 0, 0));
          pixels.show();
        }
        currentId = 0;
      }
}










