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

String newImage;


Row *rows[8] = {
    //base new Row(0b11111111, 0b11111111, 0b00001111, 0b11110000), 
    new Row(0b11111111, 0b11111111, 0b00001111, 0b10110000), 
    new Row(0b11111111, 0b11111111, 0b00001111, 0b11110000), 
    new Row(0b11111111, 0b11111111, 0b00001111, 0b11110000), 
    new Row(0b11111111, 0b11111111, 0b00001111, 0b11110000), 
    new Row(0b11111111, 0b11111111, 0b00001111, 0b11110000), 
    new Row(0b11111111, 0b11111111, 0b00001111, 0b11110000), 
    new Row(0b11111111, 0b11111111, 0b00001111, 0b11110000), 
    new Row(0b11111111, 0b11111111, 0b00001111, 0b11110000), 
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
    //Get updated rows through serial
    if (Serial.available() > 0) {
      char inByte = Serial.read();
  
      if (inByte != '#') {
        newImage += inByte;
      }
      else {
        matrixUpdate(newImage);
        newImage="";
      }
    }

  
  //draw rows through rows
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


void matrixUpdate(String imageString){
  int row = 1;
  char chars[imageString.length()+1]; 
  char currentChar;

  //convert string to array of chars
  imageString.toCharArray(chars, imageString.length()+1);
  
  for (int i = 0; i < sizeof(chars); i ++){
    
   currentChar = chars[i];
    
    switch(currentChar){
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
        //convert char to the number it represents
        row = currentChar - '0';
        break;
      case 'r':
        break;
      case 'g':
        break;
      case 'b':
        break;
    }
  }
}

/*converts bit position to an integer
 * ex: 00010000 = position 4 = 16
 */
int bitToInteger(int pos){
  int num = pow (2,8 - pos);
  
  return num
}








