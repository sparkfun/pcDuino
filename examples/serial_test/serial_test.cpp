/***************************************************************************
serial_test.cpp

Example code for serial port access on the pcDuino via C++.

26 Mar 2013 - Mike Hord, SparkFun Electronics

This code is beerware- if you find it useful, please buy me (or, for that
matter, any other SparkFun employee you met) a pint next time you meet us at
the local.

***************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "serial_test.h"

// Life is easier if we make a constant for our port name.
static const char* portName = "/dev/ttyS1";

int main(void)
{

  // The very first thing we need to do is make sure that the pins are set
  //   to SERIAL mode, rather than, say, GPIO mode.
  char path[256];
  
  for (int i = 0; i<=1; i++)
  {
    // Clear the path variable...
    memset(path,0,sizeof(path));
    // ...then assemble the path variable for the current pin mode file...
    sprintf(path, "%s%s%d", GPIO_MODE_PATH, GPIO_FILENAME, i);
    // ...and create a file descriptor...
    int pinMode = open(path, O_RDWR);
    // ...which we then use to set the pin mode to SERIAL...
    setPinMode(pinMode, SERIAL);
    // ...and then, close the pinMode file.
    close(pinMode);
  }
  
  int serialPort; // File descriptor for serial port
  struct termios portOptions; // struct to hold the port settings
  // Open the serial port as read/write, not as controlling terminal, and
  //   don't block the CPU if it takes too long to open the port.
  serialPort = open(portName, O_RDWR | O_NOCTTY | O_NDELAY );
  
  // Fetch the current port settings
  tcgetattr(serialPort, &portOptions);

  // Flush the port's buffers (in and out) before we start using it
  tcflush(serialPort, TCIOFLUSH);

  // Set the input and output baud rates
  cfsetispeed(&portOptions, B115200);
  cfsetospeed(&portOptions, B115200);

  // c_cflag contains a few important things- CLOCAL and CREAD, to prevent
  //   this program from "owning" the port and to enable receipt of data.
  //   Also, it holds the settings for number of data bits, parity, stop bits,
  //   and hardware flow control. 
  portOptions.c_cflag |= CLOCAL;
  portOptions.c_cflag |= CREAD;
  // Set up the frame information.
  portOptions.c_cflag &= ~CSIZE; // clear frame size info
  portOptions.c_cflag |= CS8;    // 8 bit frames
  portOptions.c_cflag &= ~PARENB;// no parity
  portOptions.c_cflag &= ~CSTOPB;// one stop bit
  
  // Now that we've populated our options structure, let's push it back to the
  //   system.
  tcsetattr(serialPort, TCSANOW, &portOptions);
  
  // Flush the buffer one more time.
  tcflush(serialPort, TCIOFLUSH);
  
  // Let's write the canonical test string to the serial port.
  write(serialPort, "Hello, World!", 13);

  // Now, let's wait for an input from the serial port.
  fcntl(serialPort, F_SETFL, 0); // block until data comes in 
  char dataIn;
  do
  {
    read(serialPort,&dataIn,1);
  } while(dataIn == 0);

  printf("You entered: %c\n", dataIn);

  // Don't forget to close the port! Failing to do so can cause problems when
  //   attempting to execute code in another program.
  close(serialPort);
}

void setPinMode(int pinID, int mode)
{
  writeFile(pinID, mode);
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
  int res = write(fileID, buffer, sizeof(buffer));
}
