/***************************************************************************
i2c.cpp

Example code for I2C access on the pcDuino via C++. Example is based on the
SparkFun 6DOF digital board (SEN-10121).

26 Mar 2013 - Mike Hord, SparkFun Electronics

This code is beerware- if you find it useful, please buy me (or, for that
matter, any other SparkFun employee you met) a pint next time you meet us at
the local.

***************************************************************************/

#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
  // Set up some variables that we'll use along the way
  char rxBuffer[32];  // receive buffer
  char txBuffer[32];  // transmit buffer
  int gyroAddress = 0x68; // gyro device address
  int xlAddress = 0x53;   // accelerometer device address
  int tenBitAddress = 0;  // is the device's address 10-bit? Usually not.
  int opResult = 0;   // for error checking of operations
 
  // Create a file descriptor for the I2C bus
  int i2cHandle = open("/dev/i2c-2", O_RDWR);
  
  // Tell the I2C peripheral that the device address is (or isn't) a 10-bit
  //   value. Most probably won't be.
  opResult = ioctl(i2cHandle, I2C_TENBIT, tenBitAddress);
  
  // Tell the I2C peripheral what the address of the device is. We're going to
  //   start out by talking to the gyro.
  opResult = ioctl(i2cHandle, I2C_SLAVE, gyroAddress);
  
  // Clear our buffers
  memset(rxBuffer, 0, sizeof(rxBuffer));
  memset(txBuffer, 0, sizeof(txBuffer));
  
  // The easiest way to access I2C devices is through the read/write
  //   commands. We're going to ask the gyro to read back its "WHO_AM_I"
  //   register, which contains the I2C address. The process is easy- write the
  //   desired address, the execute a read command.
  txBuffer[0] = 0x00; // This is the address we want to read from.
  opResult = write(i2cHandle, txBuffer, 1);
  if (opResult != 1) printf("No ACK bit!\n");
  opResult = read(i2cHandle, rxBuffer, 1);
  printf("Part ID: %d\n", (int)rxBuffer[0]); // should print 105
  
  // Next, we'll query the accelerometer using the same process- but first,
  //   we need to change the slave address!
  opResult = ioctl(i2cHandle, I2C_SLAVE, xlAddress);
  txBuffer[0] = 0x00;  // This is the address to read from.
  opResult = write(i2cHandle, txBuffer, 1);
  if (opResult != 1) printf("No ACK bit!\n");
  opResult = read(i2cHandle, rxBuffer, 1);
  printf("Part ID: %d\n", (int)rxBuffer[0]); // should print 229
}
