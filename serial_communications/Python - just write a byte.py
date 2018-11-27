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
ser.write( b'a:8')
time.sleep(1)
ser.write( b'a:255')
time.sleep(1)
ser.write( b'a:0')

ser.close()