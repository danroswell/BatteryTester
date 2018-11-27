import serial
import time
import re

ser = serial.Serial('COM6',9600, timeout = 10)
# Debug the serial port
# print(ser.name)

# This is needed because windows take a bit to open
# the serial port and arduino. Be patient!
time.sleep(2)

# Send a program code
# ^ = Load Program
# > = Start Program
# < = Main Menu
ser.write( b'^')

# Once the program code is sent to the arduino
# it will respond, depending on the code
ProgramResponse = ser.readline()
FixedResponse = str(ProgramResponse)
FixedResponse = FixedResponse[2:]
FixedResponse = FixedResponse.replace("\\r\\n'", "")
print(FixedResponse)

# Process the resppnse from the ardiuno
if FixedResponse == "Ready to load test program":
    # Time to load test program into the arduino
    print("Loading the program into the arduino...")
    print("Program Loaded into the arduino")
    
elif FixedResponse == "Starting the test program":
    # Acknowledge the request to start the test
    print("Arduino is starting the test...")
    print("Test Complete")
else:
    # No or invalid response
    print("Something went wrong...")

ser.close()