/***************************************************************************
gpio_test.cpp

Example code for GPIO access on the pcDuino via C++.

26 Mar 2013 - Mike Hord, SparkFun Electronics

This code is beerware- if you find it useful, please buy me (or, for that
matter, any other SparkFun employee you met) a pint next time you meet us at
the local.

***************************************************************************/

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "gpio_test.h"

// These arrays will become file descriptors for the 18 IO pin and mode files.
int pinMode[18];
int pinData[18];

int main(void)
{
  int i = 0;       // Loop iterator
  
  char inputBuffer = HIGH; // create and clear a buffer for data from pins
  
  char path[256]; // nice, long buffer to hold the path name for pin access

  // This first loop does four things:
  //   - initialize the file descriptors for the pin mode files
  //   - initialize the file descriptors for the pin data files
  //   - make the pins outputs
  //   - set all the pins low
  for (i = 2; i <= 17; i++)
  {
    // Clear the path variable...
    memset(path,0,sizeof(path));
    // ...then assemble the path variable for the current pin mode file...
    sprintf(path, "%s%s%d", GPIO_MODE_PATH, GPIO_FILENAME, i);
    // ...and create a file descriptor...
    pinMode[i] = open(path, O_RDWR);
    // ...then rinse, repeat, for the pin data files.
    memset(path,0,sizeof(path));
    sprintf(path, "%s%s%d", GPIO_PIN_PATH, GPIO_FILENAME, i);
    pinData[i] = open(path, O_RDWR); 
    // Now that we have descriptors, make the pin an output, then set it low.
    setPinMode(pinMode[i], OUTPUT);
    setPin(pinData[i], LOW);
    printf("Pin %d low\n", i);  // Print info to the command line.
  }
  
  // Now, we're going to wait for a button connected to pin 2 to be pressed
  //  before moving on with our demo.
  setPinMode(pinMode[2], INPUT_PU);
  
  do
  {
    printf("Waiting for button press...\n");
    // This lseek() is very important- must read from the top of the file!
    lseek(pinData[2], 0, SEEK_SET);
    // Read one byte from the pinData register. The first byte will be '1' if
    //   the pin is high and '0' if it is low.
    read(pinData[2], &inputBuffer, 1);
    usleep(100000);       // Sleep for 1/10 second.
  } while (inputBuffer == HIGH);
  
  // After the button press, let's scan through and turn the lights on one
  //   at a time, the back off again. After that, we're done.
  for (i = 3; i <= 17; i++)
  {
    setPin(pinData[i], HIGH);
    printf("Pin %d HIGH\n", i);
    usleep(250000);
  }
  
  for (i = 17; i >=3; i--)
  {
    setPin(pinData[i], LOW);
    printf("Pin %d LOW\n", i);
    usleep(250000);
  }
}

// These two 'set' functions are just wrappers to the writeFile() function to
//   make the code prettier.
void setPinMode(int pinID, int mode)
{
  writeFile(pinID, mode);
}

void setPin(int pinID, int state)
{
  writeFile(pinID, state);
}

// While it seems okay to only *read* the first value from the file, you
//   seemingly must write four bytes to the file to get the I/O setting to
//   work properly. This function does that.
void writeFile(int fileID, int value)
{
  char buffer[4];  // A place to build our four-byte string.
  memset((void *)buffer, 0, sizeof(buffer)); // clear the buffer out.
  sprintf(buffer, "%d", value);
  lseek(fileID, 0, SEEK_SET);   // Make sure we're at the top of the file!
  write(fileID, buffer, sizeof(buffer));
}
