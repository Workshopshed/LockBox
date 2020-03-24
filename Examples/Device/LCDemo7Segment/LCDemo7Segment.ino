#include <Key.h>
#include <Keypad.h>

#include <SoftwareSerial.h>
#define txPin 12
 
#include "LedControl.h"

LedControl lc=LedControl(12,13,10,1);
unsigned long countdown_min = 15; // change me for the countdown time!!
unsigned long countdown_millisec = countdown_min * 60 * 1000;

// Buzzer to pin 9
const int buzzer = 9;

// LCD display
byte col =0;
SoftwareSerial LCD = SoftwareSerial(0, txPin);
// since the LCD does not send data back to the Arduino, we should only define the txPin
const int LCDdelay=10;  // conservative, 2 actually works

void lcdPosition(int row, int col) {
  LCD.write(0xFE);   //command flag
  LCD.write((col + row*64 + 128));    //position 
  delay(LCDdelay);
}
void clearLCD(){
  LCD.write(0xFE);   //command flag
  LCD.write(0x01);   //clear command.
  delay(LCDdelay);
}
void backlightOn() {  //turns on the backlight
  LCD.write(0x7C);   //command flag for backlight stuff
  LCD.write(157);    //light level.
  delay(LCDdelay);
}
void backlightOff(){  //turns off the backlight
  LCD.write(0x7C);   //command flag for backlight stuff
  LCD.write(128);     //light level for off.
   delay(LCDdelay);
}
void serCommand(){   //a general function to call the command flag for issuing all other commands   
  LCD.write(0xFE);
}

void display_countdown_time() {
  unsigned long minutes = countdown_millisec / (1000UL * 60UL);
  unsigned long seconds = (countdown_millisec % (1000UL * 60UL))  / 1000;
  unsigned long milliseconds = countdown_millisec % 1000UL;
  display_digits(6, 7, minutes);
  display_digits(4, 5, seconds);
  display_digits(0, 3, milliseconds);
}

// [from, to]
void display_digits(int from, int to, int value) {
  String value_str = String(value);
  int next_digit = to;
  while(next_digit >= from+value_str.length()) {
    lc.setDigit(0, next_digit, 0, false);
    --next_digit;
  }
  for(int i=0; i<value_str.length(); ++i, --next_digit) {
    lc.setDigit(0, next_digit, value_str.charAt(i) - '0', false);
  }
}

const byte ROWS = 4; 
const byte COLS = 3; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 


void setup() {
  Serial.begin(9600);
  
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);

  pinMode(buzzer, OUTPUT);

  pinMode(txPin, OUTPUT);
  LCD.begin(9600);
  backlightOn() ;
  clearLCD();
  lcdPosition(0,0);
  LCD.print("Hello world from LinkSprite!");
  clearLCD();
}

void buzz() {
  for(int i=0; i<3; ++i) {
    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(500);         // ...for 0.5 sec
    noTone(buzzer);     // Stop sound...
    delay(500);         // ...for 0.5 sec
  }
}

void loop() {
  LCD.print("Keycode Entered");
  
  display_countdown_time();
  countdown_millisec--;

//  clearLCD();
//  Serial.write(" Hello");  // print text to the current cursor position
//  newLine();              // start a new line
//  Serial.write("Arduino");
//  delay(1000);
  
  if (countdown_millisec < 0) buzz();
}

char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
  }
}
