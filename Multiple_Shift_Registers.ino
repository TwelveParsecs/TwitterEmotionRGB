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
const int interval = 200;// >illiseconds between each frame
unsigned long startTime;

String emotion = "anger";
int frames = 2;
int currentFrame = 1;

String newImage;

String sadness[2] = {
  "1x-x-b-b-b-x-x-x-*2x-b-b-b-b-b-b-x-*3b-b-b-b-b-b-b-b-*4b-b-b-b-b-b-b-b-*5x-x-x-b-x-x-x-x-*6x-x-b-x-x-x-b-x-*7x-x-x-x-x-gb-x-x-*8x-x-x-x-b-x-x-x-*",
  "1x-x-b-b-b-x-x-x-*2x-b-b-b-b-b-b-x-*3b-b-b-b-b-b-b-b-*4b-b-b-b-b-b-b-b-*5x-b-x-x-x-b-x-x-*6x-x-x-x-gb-x-x-x-*7x-x-x-b-x-x-x-b-*8x-x-x-x-x-x-gb-x-*"
};


//String anger[2] = {
//  "1x-x-x-x-r-x-x-x-*2x-x-x-x-r-r-x-x-*3x-x-x-r-r-r-r-x-*4x-x-r-r-r-r-x-x-*5x-r-r-rg-r-x-x-x-*6x-r-rg-rg-rg-r-x-x-*7r-rg-rg-rg-rg-rg-r-x-*8x-r-rg-rg-rg-r-x-x-*",
//  "1x-x-x-x-r-x-x-x-*2x-x-x-x-r-r-x-x-*3x-x-x-r-r-r-r-x-*4x-x-r-r-r-r-x-x-*5x-r-r-rg-r-x-x-x-*6x-r-rg-rg-rg-r-x-x-*7r-rg-rg-rg-rg-rg-r-x-*8x-r-rg-rg-rg-r-x-x-*"
//};
//
//String disgust[2] = {
//  "1x-x-x-x-x-x-x-x-*2x-gb-gb-rg-rg-rg-rg-rg-*3x-gb-gb-rg-rg-rg-rg-rg-*4x-gb-gb-rg-rg-rg-rg-rg-*5x-gb-b-rg-rg-rg-rg-rg-*6x-x-x-rg-rg-rg-rg-rg-*7x-x-x-rg-rg-x-x-x-*8x-x-x-rg-rg-x-x-x-*",
//  "1x-gb-gb-rg-rg-rg-rg-rg-*2x-gb-gb-rg-rg-rg-rg-rg-*3x-gb-gb-rg-rg-rg-rg-rg-*4x-gb-b-rg-rg-rg-rg-rg-*5x-x-x-rg-rg-rg-rg-rg-*6x-x-x-rg-rg-x-x-x-*7x-x-x-rg-rg-x-x-x-*8x-x-x-x-x-x-x-x-*"
//};
//
//
//String fear[2] {
//  "1x-x-x-x-x-x-x-x-*2x-b-b-b-b-b-b-x-*3x-b-b-b-b-b-b-x-*4x-b-x-b-b-x-b-x-*5x-b-b-b-b-b-b-x-*6x-x-b-b-b-b-x-x-*7x-x-b-b-b-b-x-x-*8x-x-x-x-x-x-x-x-*",
//  "1x-x-x-x-x-x-x-x-*2x-b-b-b-b-b-b-x-*3x-b-b-b-b-b-b-x-*4x-b-x-b-b-x-b-x-*5x-b-b-b-b-b-b-x-*6x-x-b-b-b-b-x-x-*7x-x-x-x-x-x-x-x-*8x-x-b-b-b-b-x-x-*"
//};
//String joy[2] {
//  "1rg-x-x-rg-x-x-x-rg-*2x-rg-x-x-x-x-rg-x-*3x-x-x-rg-rg-x-x-x-*4rg-x-rg-rg-rg-rg-x-x-*5x-x-rg-rg-rg-rg-x-rg-*6x-x-x-rg-rg-x-x-x-*7x-rg-x-x-x-x-rg-x-*8rg-x-x-x-rg-x-x-rg-*",
//  "1x-x-x-x-rg-x-x-rg-*2rg-x-x-x-x-x-rg-x-*3x-rg-x-rg-rg-x-x-x-*4x-x-rg-rg-rg-rg-x-rg-*5rg-x-rg-rg-rg-rg-x-x-*6x-x-x-rg-rg-x-x-x-*7x-rg-x-x-x-rg-x-x-*8rg-x-x-rg-x-x-rg-x-*"
//};




Row *rows[8] = {
    //base new Row(0b11111111, 0b11111111, 0b00001111, 0b11110000), 
    new Row(0b11111111, 0b11111111, 0b00001111, 0b11110000), 
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

  startTime = millis();

}

void loop() {
    //Get updated rows through serial
    /*
    if (Serial.available() > 0) {
      char inByte = Serial.read();
  
      if (inByte != '#') {
        newImage += inByte;
      }
      else {
        matrixUpdate(newImage.substring(0,newImage.length()));
        newImage="";
      }
    }*/
  if (millis() - startTime < (interval * currentFrame)){
        String whole;
        String chunk = "";

       //if (emotion == "disgust") 
       whole = sadness[currentFrame - 1];  
       //  else
       //if (emotion == "sadness") whole = sadness[currentFrame - 1];
       //  else if (emotion == "fear")  whole = joy[currentFrame - 1];
        //else if (emotion == "disgust")  whole = disgust[currentFrame - 1];
       //else  whole = joy[currentFrame - 1];
         
        
        for (int g = 0; g < whole.length(); g ++){
          
          if (whole.charAt(g)!= '*'){
            chunk += whole.charAt(g);
          }
          else {
             chunk += "*";
            matrixUpdate(chunk);
            chunk = "";
          }
        }
          
           
  }
  else {
    if (currentFrame < frames) {
      currentFrame += 1;
    }
    else {
      currentFrame = 1;
      startTime = millis();
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
  int currentPos = 1;
  char lastChar = 'b';
  int currentRow[4] = {255,255,15,240};

  //convert string to array of chars
  imageString.toCharArray(chars, imageString.length()+1);
  
  for (int i = 0; i < sizeof(chars); i ++){
    int tempPos = 9 - currentPos; //create a reversed position for green pins
    //Serial.println(i);
    switch(chars[i]){
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
        // Convert char to the number it represents
        row = chars[i] - '0';
        //Serial.println("The row is : " + String(row));
         if (row >4){
          currentRow[3] += bitToInteger (row); //bitToInteger returns numbers 1 less than expected for some reason
          //Serial.println("Row bit : " + String( bitToInteger (row)));
        }
        else {
          currentRow[2] += bitToInteger (row);
         // Serial.println("Row bit : " + String( bitToInteger (row)));
        }
        
        break;
      case 'r':
        // Check if this is a new position
   
        // Subtract from byte
        currentRow[1] -= bitToInteger (currentPos);
        lastChar = 'r';
        break;
      case 'g':
        // Check if this is a new position
        

        // Pins for green LEDs are split between two bytes and reversed so it requires a 
        // little extra logic to turn them on correctly.
        
        if (tempPos >4){
          currentRow[3] -= bitToInteger (tempPos-4);
        }
        else {
          currentRow[2] -= bitToInteger (tempPos+4);
        }

        lastChar = 'g';
        break;
      case 'b':
        // Subtract from byte
        currentRow[0] -= bitToInteger (currentPos);
       // Serial.println("Position " + String(currentPos) + " is blue");
        
        lastChar = 'b';
        break;
      case 'x':
      if (lastChar == 'r' || lastChar =='g') currentPos +=1;
       // Serial.println("Position " + String(currentPos) + " is null");
       lastChar = 'x';
        break;
      case '-':
        currentPos += 1;
        break;
        
      case '*':
        rows[row-1]->r1 = currentRow[0];
        rows[row-1]->r2 = currentRow[1];
        rows[row-1]->r3 = currentRow[2];
        rows[row-1]->r4 = currentRow[3];
        //Serial.println("Values : " + String(currentRow[2]));
       // Serial.println("Displayed info");
        currentPos = 1;
        break;
     default :
      break;
    }
  }
}

/*converts bit position to an integer
 * ex: 00010000 = position 4 = 16
 */
int bitToInteger(int pos){
  int num = ceil(pow (2,8 - pos));
  //Serial.println("Position :" + String(pos) + "Number :" + String(num));
  return num;
}

