##############################################################################
# spi.py
#
# Example code for spi access on the pcDuino via Python. This code relies upon
# the SPI-Py library by Lous Thiery and Connor Wolf, found at
#   https://github.com/lthiery/SPI-Py
#
# 26 Mar 2013 - Mike Hord, SparkFun Electronics
#
# This code is beerware- if you find it useful, please buy me (or, for that
# matter, any other SparkFun employee you met) a pint next time you meet us at
# the local.
#
##############################################################################

#!/usr/bin/env python

import spi

## The openSPI() function is where the SPI interface is configured. There are
##   three possible configuration options, and they all expect integer values:
##   speed - the clock speed in Hz
##   mode - the SPI mode (0, 1, 2, 3)
##   bits - the length of each word, in bits (defaults to 8, which is standard)
## It is also possible to pass a device name, but the default, spidev0.0, is
##   the only device currently supported by the pcDuino.

spi.openSPI(speed=1000000, mode=0)

## Data is sent as a tuple, so you can construct a tuple as long as you want 
##   and the result will come back as a tuple of the same length.
print spi.transfer((0x0B, 0x02, 0x00))

## Finally, close the SPI connection. This is probably not necessary but it's
##   good practice.
spi.closeSPI()