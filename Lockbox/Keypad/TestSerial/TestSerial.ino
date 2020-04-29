#include <SoftwareSerial.h>

const int tx = 2;  
const int rx = 3;

SoftwareSerial serial2(rx,tx);  

void setup() {
  Serial.begin(9600);
  serial2.begin(9600);
  Serial.println("Serial Tester");
}

void loop() {
  if(serial2.available()){
    Serial.print((char) serial2.read());
  }
}
