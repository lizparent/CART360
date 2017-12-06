/*----------------------------------------------------------------------------*/
/*------------------------------ SHIFT REGISTER ------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------      IMPLEMENT THE SHIFT REGISTER FUNCTIONALITY        ----------*/
/*----------          ******** ATTRIBUTE YOUR CODE ********         ----------*/
/*----------------------------------------------------------------------------*/

#ifndef SHIFTREGISTER_H_
#define SHIFTREGISTER_H_

#include "Constants.h"

/* SHIFT REGISTER IC PIN OUTS
        __
  Q1 -|    |- VCC
  Q2 -|    |- Q0
  Q3 -|    |- DS
  Q4 -|    |- OE
  Q5 -|    |- ST_CP
  Q6 -|    |- SH_CP
  Q7 -|    |- MR
  GND -| __ |- Q'

  Key:
  Q0 - Q7: Parallel Out Pins
  Q': Cascade Pin
  DS: Serial Data In Pin
  OE: Output Enable (GND)
  ST_CP: Latch Pin
  SH_CP: Clock Pin
  MR: Master Reset (VCC)
*/

/* PINS FOR SHIFT REG */
// ST_CP of 74HC595
#define LATCH_PIN 6 //enable
// SH_CP of 74HC595
#define CLOCK_PIN 8
// DS of 74HC595
#define DATA_PIN 7

/* CONSTANT FOR EMPTY*/
#define EMPTY B11111110

/* DEFINE AND INITIALIZE THE ARRAY WITH THE NECESSARY VALUES */
// Hex Character from 0 - F
byte hexArray[16] =
{
  // you have to implement the necessary values for each element
  B10000001,  // 0 = { 1, 2, 3, 4, 5, 6 }
  B11110011,  // 1 = { 2, 3 }
  B01001001,  // 2 = { 1, 2, 4, 5, 7}
  B01100001,  // 3 = { 1, 2, 3, 4, 7}
  B00110011,  // 4 = { 2, 3, 6, 7}
  B00100101,  // 5 = { 1, 3, 4, 6, 7}
  B00000101,  // 6 = { 1, 3, 4, 5, 6, 7}
  B11110001,  // 7 = { 1, 2, 3}
  B00000001,  // 8 = { 1, 2, 3, 4, 5, 6, 7}
  B00100001,  // 9 = { 1, 2, 3, 4, 6, 7}
  B00010001,  // A = { 1, 2, 3, 5, 6, 7}
  B00000001,  // B = { 1, 2, 3, 4, 5, 6, 7}
  B00001001,  // C = { 1, 4, 5, 6}
  B10000001,  // D = { 1, 2, 3, 4, 5, 6}
  B10000111,  // E = { 1, 4, 5, 6, 7}
  B10001111,  // F = { 1, 5, 6, 7}
};

void setupShiftRegister() {
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
}

/******************sendToShiftRegister *******************************
  TODO:: IMPLEMENT THE FUNCTIONALITY TO SEND THE CORRECT DATA TO
  SHIFT REG - BASED ON THE POT VAL
********************************************************************/
void sendToShiftRegister(int pot)
{
  // IMPLEMENT
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, hexArray[pot]);
  digitalWrite(LATCH_PIN, HIGH);
  delay(20);
}

/******************READ FROM POT*********************************
  TO DO:: GET VALUE FROM POT AND ENSURE THE VALUE RETURNED IS A VALID VALUE
********************************************************************/
int getAnalog() {

  //IMPLEMENT
  //int getAnalog = 
  return analogRead(POT_PIN) / 64;
  //Serial.println(getAnalog);
  //return getAnalog;
}



#endif /* SHIFTREGISTER_H_ */

// reference: http://slab.concordia.ca/2009/arduino/shift-registers/
