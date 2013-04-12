##############################################################################
# gpio_test.py
#
# Example code for GPIO access on the pcDuino via Python
#
# 26 Mar 2013 - Mike Hord, SparkFun Electronics
#
# This code is beerware- if you find it useful, please buy me (or, for that
# matter, any other SparkFun employee you met) a pint next time you meet us at
# the local.
#
##############################################################################

#!/usr/bin/env python

import time, os

## For simplicity's sake, we'll create a string for our paths.
GPIO_MODE_PATH= os.path.normpath('/sys/devices/virtual/misc/gpio/mode/')
GPIO_PIN_PATH=os.path.normpath('/sys/devices/virtual/misc/gpio/pin/')
GPIO_FILENAME="gpio"

## create a couple of empty arrays to store the pointers for our files
pinMode = []
pinData = []

## Create a few strings for file I/O equivalence
HIGH = "1"
LOW =  "0"
INPUT = "0"
OUTPUT = "1"
INPUT_PU = "8"

## First, populate the arrays with file objects that we can use later.
for i in range(0,18):
  pinMode.append(os.path.join(GPIO_MODE_PATH, 'gpio'+str(i)))
  pinData.append(os.path.join(GPIO_PIN_PATH, 'gpio'+str(i)))

## Now, let's make all the pins outputs...
for pin in pinMode:
  file = open(pin, 'r+')  ## open the file in r/w mode
  file.write(OUTPUT)      ## set the mode of the pin
  file.close()            ## IMPORTANT- must close file to make changes!
  
## ...and make them low.
for pin in pinData:
  file = open(pin, 'r+')
  file.write(LOW)
  file.close()

## Next, let's wait for a button press on pin 2.
file = open(pinMode[2], 'r+') ## accessing pin 2 mode file
file.write(INPUT_PU)          ## make the pin input with pull up
file.close()                  ## write the changes

temp = ['']   ## a string to store the value 
file = open(pinData[2], 'r') ## open the file
temp[0] = file.read()       ## fetch the pin state

## Now, wait until the button gets pressed.
while '0' not in temp[0]:
  file.seek(0)      ## *MUST* be sure that we're at the start of the file!
  temp[0] = file.read()   ## fetch the pin state
  print "Waiting for button press..."
  time.sleep(.1)  ## sleep for 1/10 of a second.

file.close()  ## Make sure to close the file when you're done!

## Now, for the final trick, we're going to turn on all the pins, one at a
##   time, then turn them off again.
for i in range(3,17):
  file = open(pinData[i], 'r+')
  file.write(HIGH)
  file.close()
  time.sleep(.25)
  
for i in range(17,2, -1):
  file = open(pinData[i], 'r+')
  file.write(LOW)
  file.close()
  time.sleep(.25)

  