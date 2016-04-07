

//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 8;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 12;
////Pin connected to Data in (DS) of 74HC595
const int dataPin = 11;

const int latchPin2 = 2;
const int clockPin2 = 4;
const int dataPin2 = 3;


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
  registerWrite(0, HIGH);
}

void loop() {
  if (Serial.available() > 0) {
    // ASCII '0' through '9' characters are
    // represented by the values 48 through 57.
    // so if the user types a number from 0 through 9 in ASCII, 
    // you can subtract 48 to get the actual value:
    int bitToSet = Serial.read() - 48;

  // write to the shift register with the correct bit set high:
    registerWrite(bitToSet, HIGH);
  }
}

// This method sends bits to the shift register:

void registerWrite(int whichPin, int whichState) {
// the bits you want to send
byte register00 = 0b00000000;
byte register0 = 0b00000000;
  byte register1 = 0b00001111;
  byte register2 = 0b11111101;

  // turn off the output so the pins don't light up
  // while you're shifting bits:
  digitalWrite(latchPin, LOW);

  // turn on the next highest bit in bitsToSend:
  //bitWrite(bitsToSend, whichPin, whichState);
  //Serial.print (bitsToSend);
  // shift the bits out:
  shiftOut(dataPin, clockPin, MSBFIRST, register2);
  shiftOut(dataPin, clockPin, MSBFIRST, register1);
 shiftOut(dataPin, clockPin, MSBFIRST, register0);
  shiftOut(dataPin, clockPin, MSBFIRST, register00);
  
    // turn on the output so the LEDs can light up:
  digitalWrite(latchPin, HIGH);

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




