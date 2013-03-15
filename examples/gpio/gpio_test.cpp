#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// First, we'll define a path and filename constant for the virtual files which
//   represent the GPIO pins. 
#define GPIO_MODE_PATH "/sys/devices/virtual/misc/gpio/mode/"
#define GPIO_PIN_PATH "/sys/devices/virtual/misc/gpio/pins/"
#define GPIO_FILENAME "gpio"

int main(void)
{
  int i = 0; // pin number that we'll be accessing
  char path[1024]; // nice, long buffer to hold the path name for pin access
  memset(path,0,sizeof(path)); // clear the buffer
  // Next, we'll assemble our path and filename for the pin in question
  sprintf(path, "%s%s%d", GPIO_MODE_PATH, GPIO_FILENAME, i);
  int pinMode = open(path, O_RDWR);
  // Now, do the same thing for the pin instead of the mode
  memset(path,0,sizeof(path)); // clear the buffer again.
  sprintf(path, "%s%s%d", GPIO_PIN_PATH, GPIO_FILENAME, i);
  int pinName = open(path, O_RDWR);

  // Okay, so now we have two file descriptors, pinMode and pinName, which 
  //   point to files providing access to the I/O mode of a given GPIO pin,
  //   as well as the actual pin itself. Writing to these locations at address
  //   0x00 will allow you to set or clear pins, make the pin mode input, output  //   or input with pullup, etc etc. Note that the write is a four-byte value,
  //   so take that into account.

  char buffer[4];  // A place to build our four-byte string.
  memset((void *)buffer, 0, sizeof(buffer)); // clear the buffer out.
  sprintf(buffer, "%d", 0x01); // wk're going to make it an output.
  lseek(pinMode, 0, SEEK_SET);
  write(pinMode, buffer, sizeof(buffer));
  memset((void *)buffer, 0, sizeof(buffer)); // clear the buffer out.
  sprintf(buffer, "%d", 0x01); 
  lseek(pinName, 0, SEEK_SET);
  write(pinName, buffer, sizeof(buffer)); 
  sleep(2);


}
