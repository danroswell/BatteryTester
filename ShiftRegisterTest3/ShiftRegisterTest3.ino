// Pin definitions:
// The 74HC595 uses a type of serial connection called SPI
// (Serial Peripheral Interface) that requires three pins:
int datapin = 2; 
int clockpin = 3;
int latchpin = 4;

// Variables to store the incoming data bytes
String frameheader;
byte databyte1 = 0;
byte databyte2 = 0;
byte databyte3 = 0;
byte databyte4 = 0;
byte databyte5 = 0;
byte databyte6 = 0;
byte databyte7 = 0;
byte databyte8 = 0;

void setup()
{
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  // Set the three SPI pins to be outputs:
  pinMode(datapin, OUTPUT);
  pinMode(clockpin, OUTPUT);  
  pinMode(latchpin, OUTPUT);
}

void loop()
{
      // Wait for a command from the PC
      if (Serial.available() > 0) {
          // Read Frame header
          frameheader = Serial.readStringUntil(':');

          // Read the 8 Data Bytes
          databyte1 = Serial.parseInt();
          Serial.readStringUntil(',');
          databyte2 = Serial.parseInt();
          Serial.readStringUntil(',');
          databyte3 = Serial.parseInt();
          Serial.readStringUntil(',');
          databyte4 = Serial.parseInt();
          Serial.readStringUntil(',');
          databyte5 = Serial.parseInt();
          Serial.readStringUntil(',');
          databyte6 = Serial.parseInt();
          Serial.readStringUntil(',');
          databyte7 = Serial.parseInt();
          Serial.readStringUntil(',');
          databyte8 = Serial.parseInt();

          // Debugging Printouts                   
          Serial.print("Header:" + frameheader);
          Serial.print(+ " Data1:");
          Serial.print(databyte1);
          Serial.print(+ " Data2:");
          Serial.print(databyte2);
          Serial.print(+ " Data3:");
          Serial.print(databyte3);
          Serial.print(+ " Data4:");
          Serial.print(databyte4);          
          Serial.print(+ " Data5:");
          Serial.print(databyte5);          
          Serial.print(+ " Data6:");
          Serial.print(databyte6);
          Serial.print(+ " Data7:");
          Serial.print(databyte7);          
          Serial.print(+ " Data8:");
          Serial.print(databyte8);          
          Serial.println();      
      }

      // Verify frame header is valid
      // If its the right header, put the data
      // into the shift register
      if(frameheader == "a") {
          // If frame header is valid, read data
          shiftOut(datapin, clockpin, MSBFIRST, databyte1 ); 
          shiftOut(datapin, clockpin, MSBFIRST, databyte2 ); 
          shiftOut(datapin, clockpin, MSBFIRST, databyte3 ); 
          shiftOut(datapin, clockpin, MSBFIRST, databyte4 ); 
          shiftOut(datapin, clockpin, MSBFIRST, databyte5 ); 
          shiftOut(datapin, clockpin, MSBFIRST, databyte6 ); 
          shiftOut(datapin, clockpin, MSBFIRST, databyte7 ); 
          shiftOut(datapin, clockpin, MSBFIRST, databyte8 ); 

          //Toggle the latchPin to make "data" appear at the outputs
          digitalWrite(latchpin, HIGH); 
          digitalWrite(latchpin, LOW);         
      }
}
