// Pin definitions:
// The 74HC595 uses a type of serial connection called SPI
// (Serial Peripheral Interface) that requires three pins:

int datapin = 2; 
int clockpin = 3;
int latchpin = 4;

// We'll also declare a global variable for the data we're
// sending to the shift register:

String frameheader;
int Data1;
byte Data1bin;
bool Data1Array[8];

void setup()
{
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  // Set the three SPI pins to be outputs:
  pinMode(datapin, OUTPUT);
  pinMode(clockpin, OUTPUT);  
  pinMode(latchpin, OUTPUT);
}


void loop() {

      // Wait for a command from the PC
      // Format is x:yyy
      // Where x is a header (string)
      // and yyy is the data (integer from 0-255)
      if (Serial.available() > 0) {
          // Read Frame header
          frameheader = Serial.readStringUntil(':');
          Data1 = Serial.parseInt();
          ConvertToByte(Data1);

         
      Serial.print("Header: ");
      Serial.print(frameheader);
      Serial.print(" Data: ");
      Serial.print(Data1);
      Serial.print(" Data Array: ");

      for( int j = 0; j <8; j++) {
        Serial.print(Data1Array[j]);
      }
      Serial.println();
      
      }


      
      if(frameheader == "a") {
          // If frame header is valid, read data
          shiftOut(datapin, clockpin, MSBFIRST, Data1Array ); 
          //Toggle the latchPin to make "data" appear at the outputs
          digitalWrite(latchpin, HIGH); 
          digitalWrite(latchpin, LOW); 
      }
  
      delay(50);
}



void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOut�
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {  
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }

  //stop shifting
  digitalWrite(myClockPin, 0);
}

bool * ConvertToByte(int NumToConvert) {
  for(byte i=0; i<8; i++) {
    Data1Array[i] = bitRead(NumToConvert,i);
  }
  return Data1Array;
}
