#include <Key.h>
#include <Keypad.h>
#include <Adafruit_NeoPixel.h>
#define PIN            11
#define NUMPIXELS      3
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);
#include <SoftwareSerial.h>
#define txPin 12

#define Max7219DIN 7  // Pin 7 connected to DIN (DataIN)
#define Max7219CLK 6  // Pin 6 connected to CLK
#define Max7219CS 5   // Pin 5 connected to CS

#define Buzzer 8  // Pin 8 connected to Buzzer +positive pin
int BuzzTrigger=0;  // Variable to store buzzer trigger value

#include "LedControl.h"  // LedControl Library created by Eberhard Fahle at http://playground.arduino.cc/Main/LedControl

LedControl lc=LedControl(Max7219DIN,Max7219CLK,Max7219CS,1);   // Last number represent the number of Max7219 Modules connected 

long int countnumber=24001000 ; // Countdown timer start value HH:MM:SSSS

// Variables to store individual numbers
int  firstnum=0;
int  secondnum=0;
int  thirdnum=0;
int  fournum=0;
int  fivenum=0;
int  sixnum=0;
int  sevennum=0;
int  eightnum=0;

void setup() {
  lc.shutdown(0,false);  // Wake up the display
  lc.setIntensity(0,7); // Set Brightness 0-15
  lc.clearDisplay(0);  // Clear display
  pinMode(Buzzer, OUTPUT);
  digitalWrite(Buzzer, LOW);  //Buzzer Off at startup
  
  
}

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
  

  for (countnumber; countnumber != -1; countnumber --)
  {        
      String mystring = String(countnumber); // Transform Counter Int to String for manipulation
            
      // Convert number to a time value
      for (int z = 0; z < 6; z++){
             
        if ( mystring.substring(z) == "999999" ) {
          countnumber = (countnumber - 400000);
        }        

        if ( mystring.substring(z) == "9999" ) {
          countnumber = (countnumber - 4000);
        }
      }
  
//  Display number on Display depending on number of digits remaining
  if (countnumber > 9999999) {
    firstnum = ((countnumber/10000000)%10);
    secondnum = countnumber/1000000%10;
    thirdnum = countnumber/100000%10;
    fournum = countnumber/10000%10;
    fivenum = countnumber/1000%10;
    sixnum = countnumber/100%10;
    sevennum = countnumber/10%10;
    eightnum = countnumber%10;

    lc.setDigit(0,7,firstnum,false);
    lc.setDigit(0,6,secondnum,false);
    lc.setDigit(0,5,thirdnum,false);
    lc.setDigit(0,4,fournum,false);
    lc.setDigit(0,3,fivenum,false);
    lc.setDigit(0,2,sixnum,false);
    lc.setDigit(0,1,sevennum,false);
    lc.setDigit(0,0,eightnum,false);    
  }
    else {
      if (countnumber > 999999) {
//      firstnum = ((countnumber/10000000)%10);
        secondnum = countnumber/1000000%10;
        thirdnum = countnumber/100000%10;
        fournum = countnumber/10000%10;
        fivenum = countnumber/1000%10;
        sixnum = countnumber/100%10;
        sevennum = countnumber/10%10;
        eightnum = countnumber%10;

        lc.setChar(0,7,'-',false);
        lc.setDigit(0,6,secondnum,false);
        lc.setDigit(0,5,thirdnum,false);
        lc.setDigit(0,4,fournum,false);
        lc.setDigit(0,3,fivenum,false);
        lc.setDigit(0,2,sixnum,false);
        lc.setDigit(0,1,sevennum,false);
        lc.setDigit(0,0,eightnum,false);
      }   
        else {
          if (countnumber > 99999) {
//          firstnum = ((countnumber/10000000)%10);
//          secondnum = countnumber/1000000%10;
            thirdnum = countnumber/100000%10;
            fournum = countnumber/10000%10;
            fivenum = countnumber/1000%10;
            sixnum = countnumber/100%10;
            sevennum = countnumber/10%10;
            eightnum = countnumber%10;

            lc.setChar(0,7,'-',false);
            lc.setChar(0,6,'-',false);
            lc.setDigit(0,5,thirdnum,false);
            lc.setDigit(0,4,fournum,false);
            lc.setDigit(0,3,fivenum,false);
            lc.setDigit(0,2,sixnum,false);
            lc.setDigit(0,1,sevennum,false);
            lc.setDigit(0,0,eightnum,false);
          }
            else {
              if (countnumber > 9999) {
 //             firstnum = ((countnumber/10000000)%10);
 //             secondnum = countnumber/1000000%10;
 //             thirdnum = countnumber/100000%10;
                fournum = countnumber/10000%10;
                fivenum = countnumber/1000%10;
                sixnum = countnumber/100%10;
                sevennum = countnumber/10%10;
                eightnum = countnumber%10;

                lc.setChar(0,7,'-',false);
                lc.setChar(0,6,'-',false);
                lc.setChar(0,5,'-',false);
                lc.setDigit(0,4,fournum,false);
                lc.setDigit(0,3,fivenum,false);
                lc.setDigit(0,2,sixnum,false);
                lc.setDigit(0,1,sevennum,false);
                lc.setDigit(0,0,eightnum,false);
              } 
              else {
                if (countnumber > 999) {
  //              firstnum = ((countnumber/10000000)%10);
  //              secondnum = countnumber/1000000%10;
  //              thirdnum = countnumber/100000%10;
  //              fournum = countnumber/10000%10;
                  fivenum = countnumber/1000%10;
                  sixnum = countnumber/100%10;
                  sevennum = countnumber/10%10;
                  eightnum = countnumber%10;
  
                  lc.setChar(0,7,'-',false);
                  lc.setChar(0,6,'-',false);
                  lc.setChar(0,5,'-',false);
                  lc.setChar(0,4,'-',false);
                  lc.setDigit(0,3,fivenum,false);
                  lc.setDigit(0,2,sixnum,false);
                  lc.setDigit(0,1,sevennum,false);
                  lc.setDigit(0,0,eightnum,false);
                }
                else {
  //              firstnum = ((countnumber/10000000)%10);
  //              secondnum = countnumber/1000000%10;
  //              thirdnum = countnumber/100000%10;
  //              fournum = countnumber/10000%10;
  //              fivenum = countnumber/1000%10;
                  sixnum = countnumber/100%10;
                  sevennum = countnumber/10%10;
                  eightnum = countnumber%10;
  
                  lc.setChar(0,7,'-',false);
                  lc.setChar(0,6,'-',false);
                  lc.setChar(0,5,'-',false);
                  lc.setChar(0,4,'-',false);
                  lc.setChar(0,3,'-',false);
                  lc.setDigit(0,2,sixnum,false);
                  lc.setDigit(0,1,sevennum,false);
                  lc.setDigit(0,0,eightnum,false);
             }
               
            }
          }
        } 
      }
      
// If one second as gone by sound buzzer
      if (BuzzTrigger == 99){
          digitalWrite (Buzzer, HIGH) ;// Buzzer On
          delay (9) ;// Delay 2ms
          digitalWrite (Buzzer, LOW) ;// Buzzer Off 
      BuzzTrigger = 0; //  Trigger for countdown sound
      }
      else {
        delay (9);
        BuzzTrigger = BuzzTrigger + 1;
      }

// If countdown at zero sound alarm and flash display      
      if (countnumber == 0) {
        for (int y = 0; y < 8; y++){
          digitalWrite (Buzzer, HIGH) ;// Buzzer On
          for (int x = 0; x < 8; x++) 
          {
            lc.setDigit(0,x,0,false);
          } 
          delay (100) ;// Delay 1ms          
          digitalWrite (Buzzer, LOW) ;// Buzzer Off
          for (int x = 0; x < 8; x++) 
          {
            lc.setChar(0,x,'-',false);
          } 
          delay (300) ;// delay 1ms
      }
      }    
    }
}

//  clearLCD();
//  Serial.write(" Hello");  // print text to the current cursor position
//  newLine();              // start a new line
//  Serial.write("Arduino");
//  delay(1000);
  
}

char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
  }
}
