//credit to code snippets:de: [Select]
// Program..: stairway_v.1_code.pde
// Author...: l.e. hughes
// Date.....: 27 May 2011
byte incomingByte;

#define BITSB 8                        // number of bits per byte, used for code clarity
#define DATABITS 36                    // what we must send to the chip in order to control the lights
#define STARTBIT 1                     // value of the starting bit;  

const int clockPin  = 3;               // connect Arduino pin 3 to clock pin (21) on the 5450
const int dataPin   = 5;               // connect Arduino pin 6 to data pin (22) on the 5450
const int dataPin2  = 6;
const int delayTime = 200;             // delay between lights

// The following line just computes the number of bytes we will need in the ledArray to hold all of
// bits of data for the signal; it could be declared statically.
//
const int arrayLen  = (int)((DATABITS-1)/BITSB) + 1; 
const int arrayLen2  = (int)((DATABITS-1)/BITSB) + 1; 

// This is the actual array that will hold the signal bits. This program, for the 5450/5451, will 
// need 5 bytes for a total of 40 bits.
//
byte ledArray[arrayLen];               // for this chip, length is 5 and that could hold 40 values    
byte ledArray2[arrayLen2];

typedef enum {                         // this exists primarily for code clarity
 OFF, ON
} ledState;

//there are 44 leds total
//reds run off 1.9 v and 2 mA

void setup() {
// Serial port enable
Serial.begin(9600);

// declare pin 11 as output, this is the LED
//pinMode (11, OUTPUT);
 pinMode(clockPin, OUTPUT);           // we don't need a latch pin since the 5450/5451 latched after
 pinMode(dataPin,  OUTPUT);
 pinMode(dataPin2,  OUTPUT);     // receiving the 36 databits
allOff();
}

void loop() {
int buffer[3] = {0};
                               // if there is bytes available coming from the serial port
while (Serial.available()) {
  int counter = 0;
  delay(5);
  int _t = Serial.read();
    if(_t == 60) {
      
      do {
        buffer[counter] = (int)_t;
        Serial.println(buffer[counter], DEC);
        delay(15);
        _t = Serial.read();
         counter++;
      }while(counter < 3);
  }

}



//OLD
//   while(counter < 3){
//    buffer[counter++] = Serial.read();
//    Serial.println(buffer[counter]);
//   }

//int _t = Serial.read();
//if(_t == '<') {
//   buffer = (int)Serial.read(); // msg length 10
//   if(buffer != '<'){
//    Serial.println(buffer, DEC);
//   }
   //buffer = new int[_t];
   //buffer = _t;
  //int counter = 0;
//
//   while(counter < _t){
//    buffer[counter++] = Serial.read();
//    Serial.println(buffer[counter]);
//    
//   }
 //OLD END

 



                                       // message that turns all 35pins on, representing the stars, ideally fading in/out

 allOn();                             // turn all lights on
 sendDatabits();
 for(int i = 0; i<255; i++){
  analogWrite(11,i);
  delay(5);
 }
//delay(250);
//Serial.println("Done");
                                         //absolutely disgustingly formatted and simplistic argument to control LED's based on signal.
 if(buffer[1]>=33&& buffer[1]<34){
    allOff2();
 setLight2(2, ON);
    setLight2(10, ON);
     setLight2(11, ON);
      setLight2(12, ON);
       setLight2(21, ON);
   setLight2(20, ON);
    setLight2(17, ON);
    setLight2(3, ON);
     setLight2(5, ON);
      setLight2(4, ON);
       setLight2(19, ON);
        setLight2(34, ON);
      setLight2(16, ON);
      setLight2(18, ON);
      setLight2(15, ON);
      setLight2(6, ON);
       setLight2(14, ON);
      setLight2(7, ON);
      setLight2(8, ON);
      setLight2(13, ON);
      setLight2(9, ON);
      sendDatabits2();
 }else if(buffer[1]>=32&& buffer[1]<33){
    allOff2();
   setLight2(2, ON);
    setLight2(10, ON);
     setLight2(11, ON);
      setLight2(12, ON);
       setLight2(21, ON);
   setLight2(20, ON);
    setLight2(17, ON);
    setLight2(3, ON);
     setLight2(5, ON);
      setLight2(4, ON);
       setLight2(19, ON);
        setLight2(34, ON);
      setLight2(16, ON);
      setLight2(18, ON);
      setLight2(15, ON);
      setLight2(6, ON);
       setLight2(14, ON);
      setLight2(7, ON);
      setLight2(8, ON);
      setLight2(13, ON);
sendDatabits2();
 }else if(buffer[1]>=31&& buffer[1]<32){
    allOff2();
 setLight2(2, ON);
    setLight2(10, ON);
     setLight2(11, ON);
      setLight2(12, ON);
       setLight2(21, ON);
   setLight2(20, ON);
    setLight2(17, ON);
    setLight2(3, ON);
     setLight2(5, ON);
      setLight2(4, ON);
       setLight2(19, ON);
        setLight2(34, ON);
      setLight2(16, ON);
      setLight2(18, ON);
      setLight2(15, ON);
      setLight2(6, ON);
       setLight2(14, ON);
      setLight2(7, ON);
      sendDatabits2();
}  else if(buffer[1]>=29&& buffer[1]<30){
    allOff2();
 setLight2(2, ON);
    setLight2(10, ON);
     setLight2(11, ON);
      setLight2(12, ON);
       setLight2(21, ON);
   setLight2(20, ON);
    setLight2(17, ON);
    setLight2(3, ON);
     setLight2(5, ON);
      setLight2(4, ON);
       setLight2(19, ON);
        setLight2(34, ON);
      setLight2(16, ON);
      setLight2(18, ON);
      setLight2(15, ON);
      setLight2(6, ON);
      sendDatabits2();
}  else if(buffer[1]>=28&& buffer[1]<29){
    allOff2();
 setLight2(2, ON);
    setLight2(10, ON);
     setLight2(11, ON);
      setLight2(12, ON);
       setLight2(21, ON);
   setLight2(20, ON);
    setLight2(17, ON);
    setLight2(3, ON);
     setLight2(5, ON);
      setLight2(4, ON);
       setLight2(19, ON);
        setLight2(34, ON);
      setLight2(16, ON);
      sendDatabits2();
}  else if(buffer[1]>27&& buffer[1]<28){
    allOff2();
 setLight2(2, ON);
    setLight2(10, ON);
     setLight2(11, ON);
      setLight2(12, ON);
       setLight2(21, ON);
   setLight2(20, ON);
    setLight2(17, ON);
    setLight2(3, ON);
     sendDatabits2();
}  else if(buffer[1]>=26&& buffer[1]<27){
    allOff2();
 setLight2(2, ON);
    setLight2(10, ON);
     setLight2(11, ON);
      setLight2(12, ON);
       setLight2(21, ON);
   setLight2(20, ON);
    setLight2(17, ON);
    setLight2(3, ON);
     sendDatabits2();

}  else {

  allOff2();
 setLight2(2, ON);
    setLight2(10, ON);
     setLight2(11, ON);
      setLight2(12, ON);
}


allOn();
sendDatabits();
for(int i = 255; i>=0; i--){
  analogWrite(11,i);
  delay(5);
 }
//delay(250);

}

void sendDatabits() {
 digitalWrite(clockPin, LOW);
 delay(2);
 digitalWrite(dataPin, STARTBIT);
 delay(2);
 digitalWrite(clockPin, HIGH);
 delay(5);
 digitalWrite(clockPin, LOW);
 delay(2);
 for(int i = 0; i < arrayLen; i++) {
   shiftOut(dataPin, clockPin, LSBFIRST, ledArray[i]);
 }
}

void setLight(int pin, byte val) {
 byte arrayElem = int((pin-1)/BITSB);                     // which element of the ledArray is pin in
 byte byteElem  = (pin - (arrayElem * BITSB)) - 1;        // and which bit in that byte is the pin
 ledArray[arrayElem] |= (val << byteElem);                // zero vals require a two-step process, 
 if(val == 0) {                                           // first we set them to a one and then
   ledArray[arrayElem] ^= (1 << byteElem);                // toggle them
 } 
}
void allOn() {
 for(int i = 1; i < DATABITS; i++) {
   setLight(i, ON);
 }
}

void allOff() {
 for(int i = 0; i < arrayLen; i++) {
   ledArray[i] = 0;
 }
}


// for second circuit mountains

void sendDatabits2() {
 digitalWrite(clockPin, LOW);
 delay(2);
 digitalWrite(dataPin2, STARTBIT);
 delay(2);
 digitalWrite(clockPin, HIGH);
 delay(5);
 digitalWrite(clockPin, LOW);
 delay(2);
 for(int i = 0; i < arrayLen; i++) {
   shiftOut(dataPin2, clockPin, LSBFIRST, ledArray2[i]);
 }
}

void setLight2(int pin, byte val) {
 byte arrayElem2 = int((pin-1)/BITSB);                     // which element of the ledArray is pin in
 byte byteElem2  = (pin - (arrayElem2 * BITSB)) - 1;        // and which bit in that byte is the pin
 ledArray2[arrayElem2] |= (val << byteElem2);                // zero vals require a two-step process, 
 if(val == 0) {                                           // first we set them to a one and then
   ledArray2[arrayElem2] ^= (1 << byteElem2);                // toggle them
 } 
}
void allOn2() {
 for(int i = 1; i < DATABITS; i++) {
   setLight2(i, ON);
 }
}

void allOff2() {
 for(int i = 0; i < arrayLen2; i++) {
   ledArray2[i] = 0;
 }
}

