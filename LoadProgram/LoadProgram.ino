int ProgramCode = 0;   // for incoming serial data

void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
        pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

        // send data only when you receive data:
        if (Serial.available() > 0) {
                // read the incoming byte:
                ProgramCode = Serial.read();

                


                if (ProgramCode == '^') {
                  // Load the test program into the arduino
                  Serial.println("Ready to load test program");                  
                  digitalWrite(LED_BUILTIN, HIGH);
                }
                else if (ProgramCode == '>') {
                  // Begin the test
                  Serial.println("Ready to load test program");
                  digitalWrite(LED_BUILTIN, LOW);
                  
                  // Send the loaded test program to the shift registers
                }
                else {
                }
                
               
                
               
        }


        
}
 
