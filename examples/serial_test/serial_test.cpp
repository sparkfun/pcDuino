#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

// Life is easier if we make a constant for our port name.
static const char* portName = "/dev/ttyS1";

int main(void)
{
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
