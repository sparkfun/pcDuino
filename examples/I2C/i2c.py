##############################################################################
# i2c.py
#
# Example code for I2C bus access on the pcDuino via Python. Note that this
# requires the python-smbus package to be installed
#
# 26 Mar 2013 - Mike Hord, SparkFun Electronics
#
# This code is beerware- if you find it useful, please buy me (or, for that
# matter, any other SparkFun employee you met) a pint next time you meet us at
# the local.
#
##############################################################################

#!/usr/bin/env python

import smbus

## As before, we'll create an alias for our addresses, just to make things
##   a bit easier and more readable later on.
gyroAddress = 0x68
xlAddress   = 0x53

## Initialize an smbus object. The parameter passed is the number of the I2C
##   bus; for the Arduino-ish headers on the pcDuino, it will be "2".
i2c = smbus.SMBus(2)

## With both of these devices, the first byte written specifies the address of
##   the register we want to read or write; for both devices, the device ID is
##   stored in location 0. Writing that address, than issuing a read, will
##   give us our answer.
i2c.write_byte(gyroAddress, 0)
print "Device ID: " + str(i2c.read_byte(gyroAddress)) ## should be 105

i2c.write_byte(xlAddress, 0)
print "Device ID: " + str(i2c.read_byte(xlAddress)) ## should be 229
