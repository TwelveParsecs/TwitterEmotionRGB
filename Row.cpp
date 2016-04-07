//Row object holds byte data for each row

#include "Arduino.h"
#include "Row.h"
 
 Row::Row(byte r1, byte  r2, byte  r3, byte  r4){
    this->r1 = r1;
    this->r2 = r2;
    this->r3 = r3;
    this-> r4 = r4;
  }
