#include "Row.h"

//Pin connected to latch pin (ST_CP)
const int latchPin = 8;
//Pin connected to clock pin (SH_CP) 
const int clockPin = 12;
////Pin connected to Data in (DS) 
const int dataPin = 11;

const int latchPin2 = 2;
const int clockPin2 = 4;
const int dataPin2 = 3;


Row *rows[8] = {
    //base new Row(0b11111111, 0b11111111, 0b00001111, 0b11110000), 
    new Row(0b00000000, 0b11111111, 0b10001111, 0b11110000), 
    new Row(0b00000000, 0b11111111, 0b01001111, 0b11110000), 
    new Row(0b00000000, 0b11111111, 0b00101111, 0b11110000), 
    new Row(0b00000000, 0b11111111, 0b00011111, 0b11110000), 
    new Row(0b00000000, 0b11111111, 0b10001111, 0b11110000), 
    new Row(0b00000000, 0b11111111, 0b01001111, 0b11110000), 
    new Row(0b00000000, 0b11111111, 0b00101111, 0b11110000), 
    new Row(0b00000000, 0b11111111, 0b00011111, 0b11110000), 
  };


//Array holding value for each bit
bool output[32]; 

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);

  pinMode(latchPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);  
  pinMode(clockPin2, OUTPUT);
  
  Serial.begin(9600);

  for (int i = 0; i < 32; i++){
    output[i]=false;    
  }  
}

void loop() {
  for (int i = 0; i < 8; i ++){
    registerWrite(*rows[i]);  
  }
}

// This method sends bits to the shift register:

void registerWrite(Row row) {
// the bits you want to send


  // turn off the output so the pins don't light up
  // while you're shifting bits:
  digitalWrite(latchPin, LOW);
  digitalWrite(latchPin2, LOW);

  // turn on the next highest bit in bitsToSend:
  //bitWrite(bitsToSend, whichPin, whichState);
  // shift the bits out:
  shiftOut(dataPin, clockPin, MSBFIRST, row.r1);
  shiftOut(dataPin, clockPin, MSBFIRST, row.r2);
  shiftOut(dataPin2, clockPin2, MSBFIRST, row.r3);
  shiftOut(dataPin2, clockPin2, MSBFIRST, row.r4);

  
    // turn on the output so the LEDs can light up:
   digitalWrite(latchPin, HIGH);
   digitalWrite(latchPin2, HIGH);
}

byte calculateByte(bool bits[8]){
  int lastBit = 128;
  int totalByte = 0;
  for (int i = 8; i > 0; i--){
     if (bits[i]){
      totalByte += lastBit;
     }
     lastBit/=2;
  }

  return (byte)totalByte;
}










