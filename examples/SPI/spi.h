/***************************************************************************
spi.h

Header file for SPI test code for pcDuino.

26 Mar 2013 - Mike Hord, SparkFun Electronics

This code is beerware- if you find it useful, please by me (or, for that
matter, any other SparkFun employee you met) a pint next time you meet us at
the local.

***************************************************************************/

#ifndef __SPI_H__
#define __SPI_H__

// The SPI mode defines the resting polarity of the clock signal and the
//   clock edge upon which data is latched.
#define SPI_MODE0 0x00  // rest = 0, latch on rise
#define SPI_MODE1 0x01  // rest = 0, latch on fall
#define SPI_MODE2 0x02  // rest = 1, latch on fall
#define SPI_MODE3 0x03  // rest = 1, latch on rise

#define INPUT 0
#define OUTPUT 1
#define SPI 2

#define GPIO_MODE_PATH "/sys/devices/virtual/misc/gpio/mode/"
#define GPIO_FILENAME "gpio"

void writeFile(int fileID, int value);
void setPinMode(int pinID, int mode);
void configurePins(void);

#endif