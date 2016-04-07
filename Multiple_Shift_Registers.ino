

//Pin connected to latch pin (ST_CP)
const int latchPin = 8;
//Pin connected to clock pin (SH_CP) 
const int clockPin = 12;
////Pin connected to Data in (DS) 
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
  multiplex();
}

// This method sends bits to the shift register:

void registerWrite(int whichPin, int whichState) {
// the bits you want to send
  byte register1 = 0b10000001;
  byte register2 = 0b01111110;
  byte register3 = 0b11111111;
  byte register4 = 0b11111111;

  // turn off the output so the pins don't light up
  // while you're shifting bits:
  digitalWrite(latchPin, LOW);
  digitalWrite(latchPin2, LOW);

  // turn on the next highest bit in bitsToSend:
  //bitWrite(bitsToSend, whichPin, whichState);
  // shift the bits out:
   shiftOut(dataPin, clockPin, MSBFIRST, register1);
  shiftOut(dataPin, clockPin, MSBFIRST, register2);
 shiftOut(dataPin2, clockPin2, MSBFIRST, register3);
 shiftOut(dataPin2, clockPin2, MSBFIRST, register4);

  
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

void multiplex(){
  Row rows[8] = {
    //base new Row(0b11111111, 0b11111111, 0b00001111, 0b11110000), 
    new Row(0b11111111, 0b11111111, 0b00001111, 0b11110000), 
    new Row(0b10000001, 0b01111110, 0b11111111, 0b11111111), 
  }

  
  for (int i = 0; i < 8; i ++){
  
    
  }
}

//Row object holds byte data for each row
class Row 
{
  byte  r1;
  byte  r2;
  byte  r3;
  byte  r4;

  public:
  Row (byte r1, byte  r2, byte  r3, byte  r4){
    this->r1 = r1;
    this->r2 = r2;
    this->r3 = r3;
    this-> r4 = r4;
  }
};








