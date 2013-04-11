##############################################################################
# analog.py
#
# Example code for analog IO access on the pcDuino via Python.
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

## For simplicity's sake, we'll create a strings and filenames for our paths
ADC_PATH= os.path.normpath('/proc/')
ADC_FILENAME = "adc"
PWM_PATH= os.path.normpath('/sys/class/leds/')
PWM_DIR = "pwm"
PWM_FILENAME = "brightness"
PWM_MAX = "max_brightness"

## create empty arrays to store the pointers for our files
adcFiles = []
pwmFiles = []
pwmMaxFiles = []

## create an empty array to store the maximum value for each channel of PWM
pwmMaxVal = []

## Populate the arrays with paths that we can use later.
for i in range(0,6):
  adcFiles.append(os.path.join(ADC_PATH, ADC_FILENAME+str(i)))
  pwmFiles.append(os.path.join(PWM_PATH, PWM_DIR+str(i), PWM_FILENAME))
  pwmMaxFiles.append(os.path.join(PWM_PATH, PWM_DIR+str(i), PWM_MAX))

## Now, let's scan the PWM directories and pull out the values we should use
##   for the maximum PWM level.
for file in pwmMaxFiles:
  fd = open(file, 'r')
  pwmMaxVal.append(int(fd.read(16)))
  fd.close()

## Let's dim some LEDs! The method for controlling a PWM pin on the pcDuino is
##   to send to the command interpreter (via os.system() this command:
##   echo <value> > /sys/class/leds/pwmX/brightness
##   where <value> varies from 0 to the maximum value found in the
##   max_brightness file, and X can be from 0-5.
for file in pwmFiles:
  j = pwmFiles.index(file)  ## extract the PWM limit for this LED
  for i in range (0,pwmMaxVal[j]):
    os.system("echo " + str(i) + " >" + file)
    time.sleep(.01)
  os.system("echo 0 >" + file)
    
## Reading ADC values is a little more straightforward than PWM- it's just
##   classic OS file reads. Note that the value that comes out of the file is
##   a string, so you'll need to format it with int() if you want to do math
##   with that value later on!
for file in adcFiles:
  fd = open(file, 'r')
  fd.seek(0)
  print "ADC Channel: " + str(adcFiles.index(file)) + " Result: " + fd.read(16)
  fd.close()
  