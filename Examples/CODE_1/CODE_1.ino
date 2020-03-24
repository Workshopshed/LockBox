#include <Keypad.h>
#include <Adafruit_NeoPixel.h>
#define PIN            11
#define NUMPIXELS      3
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);

#include <SoftwareSerial.h>
 #define buzzer 9
#define txPin 12
 byte col =0;
SoftwareSerial LCD = SoftwareSerial(0, txPin);
// since the LCD does not send data back to the Arduino, we should only define the txPin
const int LCDdelay=10;  // conservative, 2 actually works

const byte numRows= 4; //number of rows on the keypad
const byte numCols= 4; //number of columns on the keypad
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
/*keymap defines the key pressed according to the row and columns just as appears on the keypad*/
char keymap[numRows][numCols]=
{
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[numRows] = {9,8,7,6}; //Rows 0 to 3
byte colPins[numCols]= {5,4,3,2}; //Columns 0 to 3
char codeEntered[4];
char correctCode[4]= {'1','1','1','1'};
//initializes an instance of the Keypad class
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

void setup()
{

  pinMode(txPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  LCD.begin(9600);
  backlightOn() ;
  clearLCD();
  lcdPosition(0,0);
  LCD.print("Hello world from LinkSprite!");
//  clearLCD();
  pixels.begin();
  for(int i=0;i<NUMPIXELS;i++){
                              pixels.setPixelColor(i, pixels.Color(0,0,0));}
                              pixels.show();
}

//If key is pressed, this key is stored in keypressed variable
//If key is not equal to NO_KEY, then this key is printed out
//if count=17, then count is reset back to 0 (this means no key is pressed during the whole keypad scan process
void loop()
{
  char keypressed = myKeypad.getKey();
  if (keypressed != NO_KEY)
    {
                                  for(int i=0;i<NUMPIXELS;i++){
                              pixels.setPixelColor(i, pixels.Color(0,0,0));}
                              pixels.show();
                              
           digitalWrite(buzzer, 1);
           delay(100);
           digitalWrite(buzzer, 0);
           if(keypressed =='#')
            {
              clearLCD();
              col =0;
              LCD.print("Keycode Entered");
                    if(codeEntered[0] == correctCode[0]&&codeEntered[1] == correctCode[1]&&codeEntered[2] == correctCode[2]&&codeEntered[3] == correctCode[3])
                            {
                              clearLCD();
                              LCD.print("Correct Code");
                              for(int i=0;i<NUMPIXELS;i++){
                              pixels.setPixelColor(i, pixels.Color(0,50,0));}
                              pixels.show();
                            }
                            else{
                                clearLCD();
                                  LCD.print("Error Code");
                                    for(int i=0;i<NUMPIXELS;i++){
                              pixels.setPixelColor(i, pixels.Color(50,0,0));}
                              pixels.show();
                                 }
      delay(1000);
      clearLCD();
      }
      else{
      lcdPosition(0,col);
      LCD.print(keypressed);
      codeEntered[col] = keypressed;
      col++;

      }
      if (col >5)
      {
               clearLCD();
               
        col =0; 
      }
    }
}
