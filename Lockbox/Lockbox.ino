#include "Delay.h"  
#include <SoftwareSerial.h>

/* 
 * RX is digital pin 2 - Connect to the keypad
 * TX is digital pin 3 - Connect to the data pin on the screen
 */

NonBlockDelay mainTimer; 
NonBlockDelay displayTimer;
NonBlockDelay tickTimer;
   
enum boxStates {
  ARMED_0, 
  ARMED_1, 
  ARMED_2,
  ARMED_3,
  BOOM,
  DEACTIVATED
};

enum boxStates boxState;
String keyCode;
unsigned long interval=0;
unsigned long previousMillis=0;
int tickRate = 5000;

String const keyCode_Init = "0000#";
String const keyCode_1 = "9374#";
String const keyCode_2 = "1564#";
String const keyCode_3 = "7132#";
String const keyCode_4 = "3684#";

SoftwareSerial keyDisplay(2, 3); // RX, TX

void setup() {
  keyDisplay.begin(9600);
  
   // Set display 20x4  
  keyDisplay.write(5);
  keyDisplay.write(4);
  keyDisplay.write(20);
  keyDisplay.write(0xFF); 
  
  // Set backlight on bright
  keyDisplay.write(7);
  keyDisplay.write(250);  
  keyDisplay.write(0xFF);   
  
  clearDisplay();
  
  StartTimer();
  boxState = ARMED_0;
  keyCode = keyCode_Init;

  writeState("Armed");
}

void clearDisplay() {
  keyDisplay.write(4);
  keyDisplay.write(0xFF);   
  setPosDisplay(1,1);
}

void writeDisplay(char *msg) {
  keyDisplay.write(1);
  keyDisplay.print(msg);
  keyDisplay.write(0xFF);  
}

void writeState(char *msg) {
    setPosDisplay(1,1);
    writeDisplay(msg);
    setPosDisplay(2,1);
    writeDisplay("State:");
    setPosDisplay(2,8);
    char buffer [3];
    itoa (boxState,buffer,10);
    writeDisplay(buffer);
}

void setPosDisplay(int row, int col) {
  // Move to line 2 column 1
  mySerial.write(2);
  mySerial.write(row);
  mySerial.write(col);  
  mySerial.write(0xFF); 
 
}

void loop() {
  CheckKeys();
  UpdateStatus();
  UpdateDisplay();
  //Display counter
  //Display LEDs  
}

void CheckKeys() {
  // Using Serial to temporarily to pretend to be a keypad
  // Might need to do some tuning here. e.g. available() > 4
  if (keyDisplay.available() > 0) {
    String keys = keyDisplay.readString();
    if (keys.substring(4,5) == "#") {
        keyCode = keys.substring(0,5);
    }
  }
}

void StartTimer() {
  //Important: Need "L" so that the value passed in is a long not an int
  mainTimer.CountDown(1000L * 60L * 60L * 10L); // Todo: Implement the user entry for the timeout, default to 10 mins
  tickTimer.CountDown(5000);
}

void UpdateStatus() {
  if (boxState == DEACTIVATED) {
    return; 
  }
  
  if (mainTimer.OutofTime()) {
    writeDisplay("BOOM!");
    boxState = BOOM;
    return;
  }
  //Serial.println(keyCode);
  //Serial.println(boxState);
  
  if (keyCode == keyCode_1 && boxState == ARMED_0) {
    boxState = ARMED_1;
    CodeAccepted();
    return;
  }
  if (keyCode == keyCode_2 && boxState == ARMED_1) {
    boxState = ARMED_2;
    CodeAccepted();
    return;
  }
  if (keyCode == keyCode_3 && boxState == ARMED_2) {
    boxState = ARMED_3;
    CodeAccepted();
    return;
  }
  if (keyCode == keyCode_4 && boxState == ARMED_3) {
    boxState = DEACTIVATED;
    CodeAccepted();
    return;
  }
  if (keyCode != "0000#") {
    CodeWrong();
  }
  
}

void CodeWrong() {
    // Speed up if wrong code entered
    displayTimer.CountDown(1000 * 3);
    writeState("WRONG CODE ");
    mainTimer.Skip(1000 * 30);
    keyCode = keyCode_Init;
    tickRate = tickRate * 0.8;
}

void CodeAccepted() {
    displayTimer.CountDown(1000 * 3);
    writeState("CODE ACCEPTED");
    keyCode = keyCode_Init;
}

void UpdateDisplay() {
  //Serial.println(mainTimer.RemainingTime());
  
  if (displayTimer.OutofTime()) {
     clearDisplay();
  }

  if (tickTimer.OutofTime()) {
    clearDisplay();
    writeDisplay("TICK");
    tickTimer.CountDown(tickRate);
    displayTimer.CountDown(1000 * 3);
  }
}
