/***************************************************************************
serial_test.h

Header file for serial port test code for pcDuino.

11 Apr 2013 - Mike Hord, SparkFun Electronics

This code is beerware- if you find it useful, please buy me (or, for that
matter, any other SparkFun employee you met) a pint next time you meet us at
the local.

***************************************************************************/

#ifndef __SERIAL_TEST_H__
#define __SERIAL_TEST_H__

#define SERIAL 3

#define GPIO_MODE_PATH "/sys/devices/virtual/misc/gpio/mode/"
#define GPIO_FILENAME "gpio"

void writeFile(int fileID, int value);
void setPinMode(int pinID, int mode);
void configurePins(void);

#endif