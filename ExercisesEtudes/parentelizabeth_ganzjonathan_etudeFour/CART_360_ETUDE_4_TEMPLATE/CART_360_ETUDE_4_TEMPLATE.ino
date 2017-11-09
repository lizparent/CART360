/**********************ETUDE 4 CART 360 2017*******************************
   1/ As in Etude 3, in Etude 4 you will still Play & Record Notes and capture the associated Note Duration.
   Additionally, in the record() , Pauses between Notes are also captured - you need to implement.
   2/In Playback Mode, you will NOW have the option to Store the Pattern of Notes you just recorded by pressing the Store Button -
   3/ You will be able to store up to 16 Patterns (Hardcoded Limit).
   4/ Loop Mode has been Deprecated and has been replaced by the new Retrieve Mode ( retrieveMode() ).
   In Retrieve Mode, you will be able to Select a Stored Pattern and Retrieve it
   - the Stored Pattern Number will be displayed on the 7-Segment Display.
   To Play the Stored Pattern, you will Press the Store Button (Confirm Selection).
   The Potentiometer, Shift Register and 7-Segment Display work in concert to support your intention:
   In Retrieve Mode, the Potentiometer selects Pattern ID -> Sends Pattern ID to Shift Register -> Shift Register to 7-Segment Display.
*/
#include "Constants.h"
#include "InterruptHandler.h"
#include "ShiftRegister.h"
#include "TestPattern.h"
#include "Timer.h"

/******** VARIABLES *****************************************************/
// counter for how many notes we have
int countNotes = 0;
// array to hold the notes played (for record/play mode)
int notes [MAX_NOTES];
int mode = 0; //

/******** VARIABLES FOR ETUDE 3 *****************************************************/
// NEW FOR ETUDE 3: array to hold durations
// will be a parallel array to the notes array -
// meaning that at index 0 of notes[] is stored the 1st frequency, and at index 0 of
// the durations array  is stored the 1st duration for THAT note....
int durations [MAX_NOTES];
int durations_In_Between[MAX_NOTES];

// boolean to determine if a note button was being pressed:
boolean activeNoteButton = false;

// keep track of the active frequency
int activeFrequency = 0;

// var to hold the note pressed
int testNote;

// var to hold a reference to the timer object used for finding the note durations
Timer t1;

// ** NEW :: this timer object YOU will need to use  for finding pauses BETWEEN notes
Timer t_between;

/**********************SETUP() DO NOT CHANGE*******************************/
// Declare pin mode for the single digital input
void setup()
{
  Serial.begin(9600);

  // INTERRUPT HANDLER
  setupInterruptHandler();

  // SHIFT REGISTER
  setupShiftRegister();
  // sendToShiftRegister(EMPTY);
}
/**********************LOOP() *******************************
   INSTRUCTIONS:
   The loop establishes the flow of the program:
   If the mode Button has been pressed (modeChangeInterruptRequest boolean == true) then:
   1: chooseMode():  &&&
   2. YOU need to ensure that the  7-SEGMENT DISPLAY is off.
   Then  - regardless of if the button is pressed:
   3: setRGB(): will set the color of the RGB LED based on the value of the mode variable
   4: selectMode(): will determine which function to call based on the value of the mode variable
**************************************************************************/
void loop()
{
  //
  if (modeChangeInterruptRequest)
  {
    chooseMode();
    delay(DURATION * 2);

    modeChangeInterruptRequest = ISFALSE;
    /* TO DO ::: TURN OFF THE 7-SEGMENT DISPLAY */
    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, EMPTY);
    digitalWrite(LATCH_PIN, HIGH);
    delay(25);
  }
  setRGB();
  selectMode();
}
/******************CHOOSEMODE() -NOTHING TO CHANGE *********************************
   INSTRUCTIONS:
   Read the value from the Button (linked to the BUTTON_MODE_PIN) and
   if is being pressed then change the mode variable.

   REMEMBER:
   mode == 0 is reset
   mode == 1 is live
   mode == 2 is record
   mode == 3 is play
   mode == 4 is retrieve mode
   Every time the user presses the button, the program will go to the next mode,
   once it reaches 4, it should go back to mode == 0.
   (i.e. if mode ==2 and we press, then mode ==3) ...
**************************************************************************/
void chooseMode() {

  if (mode < 4) mode++;
  else mode = 0;
}
/**********************SELECTMODE() - NOTHING TO CHANGE *******************************
   INSTRUCTIONS:
   There is NO NEED to change this function - it selects WHICH function should run based on the mode variable
   There are 4 possibilities
   1: reset(): this function will reset any arrays etc, and will do nothing else
   2: live(): this function will play the corresponding notes
   to the user pressing the respective buttons.
   NOTE:: the notes played are NOT stored
   3: recordWithDuration(): this function will play the corresponding notes
   to the user pressing the respective buttons
   AND will STORE up to 16 consecutive notes in an array.
   4: playWithDuration(): this function will playback any notes stored in the array that were recorded
   in the previous mode AND allow the user to store the pattern.
   5: retrieve():

******************************************************************************/
void selectMode()
{
  if (mode == 0) {
    reset();
  }
  else if (mode == 1) {
    live();
  }
  else if (mode == 2) {
    recordWithDuration();
  }
  else if (mode == 3) {
    playWithDuration();
  }
  else if (mode == 4) {
    retreiveMode();
  }
}
/******************RESET() **************************************
   INSTRUCTIONS:
   this function should ensure that any notes recorded are no longer available
   ALSO: to IMPLEMENT: turn off the SEVEN SEGMENT DISPLAY
**************************************************************************/
void reset() {
  countNotes = 0;
  noTone(BUZZER_PIN);
  storeOnce = ISFALSE;
  /* TO DO:: TURN OFF THE 7-SEGMENT DISPLAY */
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, EMPTY);
  digitalWrite(LATCH_PIN, HIGH);
  delay(25);
}
/******************LIVE()- NOTHING TO DO **************************************
   INSTRUCTIONS:
   this function will play the corresponding notes
   to the user pressing the respective buttons
   NOTE:: the notes played are NOT stored
   SO: you need read in the input from the analog input (linked to the button-resistor ladder combo)
   ALSO - get the value of the photo cell and combine it with the note frequency
   THEN - output the note to the buzzer using the tone() function, as 3rd argument
   make the duration value == to 100
**************************************************************************/
void live() {
  Serial.println(analogRead(NOTE_IN_PIN));
  if (analogRead(NOTE_IN_PIN) > 80) {
    tone(BUZZER_PIN, analogRead(NOTE_IN_PIN), 100);
  }
  // make sure that in record mode we cannot save a pattern
  if (storePatternInterruptRequest == ISTRUE)
  {
    storePatternInterruptRequest = ISFALSE;
  }
}
/******************RECORDWITHDURATION(): IMPLEMENT NEW ETUDE 4 ************
   INSTRUCTIONS:
   YOU need to implement the new functionality for capturing the pauses between notes ...
   HINT: you will need to use the second timer and at some point call the  addToArrayInBetween() function which will
   update the necessary data structures.
   THERE IS NO INDICATION WHERE OR HOW YOU SHOULD DO THIS IN THIS FUNCTION
**************************************************************************/
void recordWithDuration()
{
  int theAdjuster = 80;
  // check we have not stored more than 16 notes
  if (countNotes < MAX_NOTES) {
    // read in the value from button press
    testNote = analogRead(NOTE_IN_PIN);
    /*** STATE A::: *****************************************
        IF the testNote is > min AND the timer has not reached 5 secs:
        This means we are pressing on a note button
    */

    if (testNote > theAdjuster && (t1.getTimePassed() < MAX_PRESS_TIME)) {
      /*** STATE AA::: *****************************************
          IF the boolean is false it means we have just started to press the button
          YOU now need to implement the function below which will set up all things
          required to have a new timer
      */
      if (activeNoteButton == ISFALSE) {
        t_between.updateTimer();
        addToArrayInBetween();
        t1.startUpTimer();
        activeNoteButton = ISTRUE;
      }
      /*** STATE AA::: *****************************************
           IF the boolean is true it means we are continuing to press the button
      */
      else {
        // update the timer (for durations)
        t1.updateTimer();
        activeFrequency = testNote;
        playCurrentNote();
      }
    }
    /*** STATE B::: *****************************************
       IF the testNote is > min AND the timer HAS reached 5 secs:
       then turn OFF the buzzer.
    */
    else if (testNote > theAdjuster && (t1.getTimePassed() > MAX_PRESS_TIME)) {

      noTone(BUZZER_PIN);


    }
    /*** STATE C::: *****************************************
       IF the testNote is < min AND the boolean is true
       this means we have STOPPED pressing the button, update the arrays
    */
    else if ((testNote <= theAdjuster && activeNoteButton == ISTRUE) ) {
      /*** FUNCTION TO IMPLEMENT ***/
      updateArraysWithNoteAndTimings();
    }

    else if ((testNote <= theAdjuster && activeNoteButton == ISFALSE) ) {
      /*** FUNCTION TO IMPLEMENT ***/
      t_between.updateTimer();
    }

  }



  // make sure that in record mode we cannot save a pattern
  if (storePatternInterruptRequest == ISTRUE)
  {
    storePatternInterruptRequest = ISFALSE;
  }
}


/******************PLAYCURRENTNOTE(): *******************************
   INSTRUCTIONS:
   this function will play the current note being pressed in RecordDuration mode
**************************************************************************/
void playCurrentNote() {
  tone(BUZZER_PIN, activeFrequency, 100);

}
/******************UPDATEARRAYSWITHNOTEANDTIMINGS():SMALL CHANGE **********
   INSTRUCTIONS:
   this function handles the case where the note is no longer being pressed:
   you need to update the arrays
   reset the necessary booleans
   reset any counters
   //TO DO :: perhaps we want to start up our other timer ????
**************************************************************************/
void updateArraysWithNoteAndTimings() {
  notes[countNotes] = activeFrequency;
  durations[countNotes] = t1.getTimePassed();
  countNotes++;
  activeNoteButton = ISFALSE;
  t1.setTimePassed(0);
  //start new timer array

  t_between.startUpTimer();
}
/******************addToArrayInBetween(): IMPLEMENT *******************************
   INSTRUCTIONS:
   this function will handle the case that adds the current pause into the necessary array
   You may also need to reset some variables....
  /*************************************************************************/
void addToArrayInBetween() {
  // IMPLEMENT
  //populate the new array with the duration of pauses, then reset the timer
  if (countNotes > 0)
  {
    durations_In_Between[countNotes - 1] = t_between.getTimePassed();
    t_between.setTimePassed(0);
  }
}
/******************PLAYWITHDURATION(): ADAPTED FOR ETUDE 4 *******************
   INSTRUCTIONS:
   this function goes through the notes array and play back the note and
   its corresponding duration value.
   TO IMPLEMENT:: add the ability to store the current sequence playing within the if statement
**************************************************************************/
void playWithDuration() {
  int i = 0;
  while (storePatternInterruptRequest == ISFALSE && modeChangeInterruptRequest == ISFALSE ) {
    if (countNotes > 0) {
      tone(BUZZER_PIN, notes[i], durations[i]);
      delay(durations[i]);
      // ensure that you have values in this array ...
      delay(durations_In_Between[i]);
      if (i < countNotes) i++;
      else {
        i = 0;
        delay(DURATION);
      }
    }
  }

  if (countNotes > 0 && storePatternInterruptRequest == ISTRUE && storeOnce == ISFALSE)
  {
    // TODO:: add pattern to our list
    //HINT use the TestPattern files..... there is a specific function that one can do to do this...
    //keep
    addPattern(notes, durations, durations_In_Between, countNotes);
    storeOnce = ISTRUE;

    /* TO DO::: FLASH THE LED ON AND OFF for DURATION (once) */
    analogWrite(LED_PIN_R, 0);   // Turn on the LED -R
    analogWrite(LED_PIN_G, 0);   // Turn on the LED -G
    analogWrite(LED_PIN_B, 0);   // Turn on the LED -B
    delay(DURATION);
    analogWrite(LED_PIN_R, 0);   // Turn on the LED -R
    analogWrite(LED_PIN_G, 255);   // Turn on the LED -G
    analogWrite(LED_PIN_B, 0);   // Turn on the LED -B

  }
  delay(DURATION * 2);
  storePatternInterruptReset();
}
/******************HELPER STATE 0 - PARTIALLY IMPLEMENT *******************
      INSTRUCTIONS: while neither button is pressed then:
      1/ get pot value
      2/if we have do NOT have a valid index (i.e. we selected "3" but there are only 3 patterns not 4) then
      make sure the seven segment display blinks.
      3/ otherwise, make sure that the shift register sends the correct number to the seven segment display


**************************************************************************/
void selectThePatternWithPot_Stage_0_(int & shiftRef)
{
  while (storePatternInterruptRequest == ISFALSE && modeChangeInterruptRequest == ISFALSE) {
    //1::YOU NEED TO IMPLEMENT THIS FUNCTION IN SHIFTREGISTER.h
    shiftRef = getAnalog();

    if (isValidIndex(shiftRef) == ISFALSE) {
      //2:: IMPLEMENT (again you will use functions that you implemented in SHIFTREGISTER.h)
      digitalWrite(LATCH_PIN, LOW);
      shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, B11111111);
      digitalWrite(LATCH_PIN, HIGH);

      delay(DURATION);
      
      digitalWrite(LATCH_PIN, LOW);
      shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, B11111110);
      digitalWrite(LATCH_PIN, HIGH);
      
      delay(DURATION);
    }
    // is valid index
    else {
      //3::IMPLEMENT (again you will use functions that you implemented in SHIFTREGISTER.h)
      sendToShiftRegister(shiftRef);

    }
  }
}
/******************HELPER STATE 1 -PARTIALLY IMPLEMENT *********************************
      INSTRUCTIONS:
  While the modebutton is not pressed: if we have a valid index
  then:
  1/ use the TestPattern functions to retrieve the notes,
  durations and pauses for that pattern.
  2/  Then play the current pattern
**************************************************************************/
void retrieveThePatternAccordingToSelection_Stage_1(int & shiftRef)
{
  while (modeChangeInterruptRequest == ISFALSE) {
    if (isValidIndex(shiftRef) == ISTRUE) {
      //1: TO DO :::RETRIEVE THE NOTES, PAUSES AND DURATIONS
      //HINT::: you will need to return a reference from the appropriate testPattern function
      // the FIRST one is given to you - the others will follow the same idea
      const int * noteArray = retrievePatternNotes(shiftRef);
      const int * durationsArray = retrievePatternDurations(shiftRef);
      const int * pausesArray = retrievePatternPauses(shiftRef);
      // you do::
      // const int * durationsArray = ....
      // const int * pausesArray =  ...

      //2: TODO: play the current pattern:
      //HINT: getNumberNotesOfPattern(shiftRef) -> will give you the number of notes in the pattern
      for (int i = 0; i < getNumberNotesOfPattern(shiftRef); i++) {
        tone(BUZZER_PIN, noteArray[i], durationsArray[i]);
        delay(pausesArray[i]);
      }

    }
  }
}
/******************RETRIEVEMODE(): IMPLEMENT *********************************
   INSTRUCTIONS:
   1/ while there are no patterns and the mode button is not pressed then blink the
   seven segment display for DURATION
   2/ otherwise select the pattern and perhaps retrieve it


**************************************************************************/
void retreiveMode()
{
  noTone(BUZZER_PIN);
  static int shift = -1;

  while (patternListIsEmpty() == ISTRUE && modeChangeInterruptRequest == ISFALSE) {
    //1:: Implement - again you will use the functions you implemented in shiftRegister.h
    //blink dp
      digitalWrite(LATCH_PIN, LOW);
      shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, B11111111);
      digitalWrite(LATCH_PIN, HIGH);

      delay(DURATION);
      
      digitalWrite(LATCH_PIN, LOW);
      shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, B11111110);
      digitalWrite(LATCH_PIN, HIGH);

      delay(DURATION);
  }

  // not empty case::
  //(PLEASE IMPLMENT THIS FUNCTION)
  selectThePatternWithPot_Stage_0_(shift);

  // we will come here because the store button was pressed  -> so we go to next stage - (store that pattern)
  delay(DURATION * 2);
  storePatternInterruptReset();

  // store and play the pattern until the mode button is pressed (PLEASE IMPLMENT THIS FUNCTION)
  retrieveThePatternAccordingToSelection_Stage_1(shift);
}

/******************SETRGB() - NOTHING TO DO*********************************
   INSTRUCTIONS:
   Depending on the value of the mode variable:
   if the mode is 0 - RGB LED IS OFF
   if the mode is 1 - RGB LED IS BLUE
   if mode is 2 - RGB LED IS RED
   if mode is 3 - RGB LED IS GREEN
   if mode is 4 - RGB LED iS PURPLE
   YOU MUST USE A SWITCH CASE CONSTRUCT (NOT A SERIES OF IF / ELSE STATEMENTS
**************************************************************************/
void setRGB()
{
  switch (mode)
  {
    case 0:
      {
        analogWrite(LED_PIN_R, 0);   // Turn on the LED -R
        analogWrite(LED_PIN_G, 0);   // Turn on the LED -G
        analogWrite(LED_PIN_B, 0);   // Turn on the LED -B
        break;
      }
    case 1:
      {
        analogWrite(LED_PIN_R, 0);   // Turn on the LED -R
        analogWrite(LED_PIN_G, 0);   // Turn on the LED -G
        analogWrite(LED_PIN_B, 255);   // Turn on the LED -B
        break;
      }
    case 2:
      {
        analogWrite(LED_PIN_R, 255);   // Turn on the LED -R
        analogWrite(LED_PIN_G, 0);   // Turn on the LED -G
        analogWrite(LED_PIN_B, 0);   // Turn on the LED -B
        break;
      }
    case 3:
      {
        analogWrite(LED_PIN_R, 0);   // Turn on the LED -R
        analogWrite(LED_PIN_G, 255);   // Turn on the LED -G
        analogWrite(LED_PIN_B, 0);   // Turn on the LED -B
        break;
      }

    case 4:
      {
        analogWrite(LED_PIN_R, 125);   // Turn on the LED -R
        analogWrite(LED_PIN_G, 0);   // Turn on the LED -G
        analogWrite(LED_PIN_B, 255);   // Turn on the LED -B
        break;
      }
  }
}

/**************************************************************************
  Anwser the  questions IN THIS SPACE....
  1. Shift register is used to send serial commands from the arduino to the additional pins that the shift register controls, allowing the arduino to extend its control to more pins than it would normally have access to.
  It is indeed how we use it in this etude, as we use the arduino to tell the shift register which led's on the display to light up.


  2.The simplest way of being able to play each stored sequence without needed to loop back around the whole way would be to set a trigger when the playback button is pressed: it would play the song that correlates with the index that the pot chooses, but when pressed again starts playing whatever value is now displayed on the pot, allowing you to start playing one and cycle through looking for more you might want to play.


  3.A potential way to store the modulation would be to create a massive array that not only stores the notes, but also stores the changes per note. The change would be captured every time the duration timer updated itself, and it would capture the full change across the note. The difficult part would be syncing up the array in such a way that the full change accross the note is played for the proper note and duration.


  4.While this instrument is a buldup of our knowledge involving circuitry and coding, a really cool addition to the instrument would be its connection to things outside itself. With serial communication being made between the shiftReg and the arduino, having the instrument communicate with the attached computer or an additional component and have serial dialogue between them would be an interesting expansion on the circuit and serial communication.
  Another part that can be expanded on is indeed divorced from the coding aspect and is very focused on the physical. When working on projects one off the hardest parts when making the physical is making sure nothing break or disconnects when it is being implemented. While likely harder to grade, the addition of making some sort of holding case or physical attachement would be a nice foray into making circuits that can iether withstand movement or have a specific form in mind before they are built.





  /**************************************************************************/


