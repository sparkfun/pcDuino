##############################################################################
# serial_test.py
#
# Example code for serial port access on the pcDuino via Python. Note that
# this example assumes that you have the pyserial library installed on your
# system.
#
# 26 Mar 2013 - Mike Hord, SparkFun Electronics
#
# This code is beerware- if you find it useful, please buy me (or, for that
# matter, any other SparkFun employee you met) a pint next time you meet us at
# the local.
#
##############################################################################

#!/usr/bin/env python

import serial ## Load the serial library

## Select and configure the port
myPort = serial.Serial('/dev/ttyS1', 115200, timeout = 10)

## Dump some data out of the port
myPort.write("Hello, world!")

## Wait for data to come in- one byte, only
x = myPort.read()

## Echo the data to the command prompt
print "You entered " + x

## Close the port so other applications can use it.
myPort.close()
