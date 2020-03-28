#include "Delay.h"  
  
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

void setup() {
  Serial.begin(9600);
  StartTimer();
  boxState = ARMED_0;
  keyCode = keyCode_Init;
  Serial.println("Armed");
  Serial.print("State:");
  Serial.println(boxState,DEC);
}

void loop() {
  CheckKeys();
  UpdateStatus();
  UpdateDisplay();
}

void CheckKeys() {
  // Using Serial to temporarily to pretend to be a keypad
  if (Serial.available() > 0) {
    String keys = Serial.readString();
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
    Serial.println("BOOM!");
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
    Serial.println("WRONG CODE");
    Serial.print("State:");
    Serial.println(boxState,DEC);
    mainTimer.Skip(1000 * 30);
    keyCode = keyCode_Init;
    tickRate = tickRate * 0.8;
}

void CodeAccepted() {
    displayTimer.CountDown(1000 * 3);
    Serial.println("CODE ACCEPTED");
    Serial.print("State:");
    Serial.println(boxState,DEC);
    keyCode = keyCode_Init;
}

void UpdateDisplay() {
  //Serial.println(mainTimer.RemainingTime());
  
  if (displayTimer.OutofTime()) {
    //Clear screen
  }

  if (tickTimer.OutofTime()) {
    Serial.println("TICK");
    tickTimer.CountDown(tickRate);
  }
  //Display counter
  //Display LEDs
}
