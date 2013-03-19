#ifndef __SPI_H__
#define __SPI_H__

// The SPI mode defines the resting polarity of the clock signal and the
//   clock edge upon which data is latched.
#define SPI_MODE0 0x00  // rest = 0, latch on rise
#define SPI_MODE1 0x01  // rest = 0, latch on fall
#define SPI_MODE2 0x02  // rest = 1, latch on fall
#define SPI_MODE3 0x03  // rest = 1, latch on rise

#define SPI_CLOCK_DIV1   0x00
#define SPI_CLOCK_DIV2   0x01
#define SPI_CLOCK_DIV4   0x02
#define SPI_CLOCK_DIV8   0x03
#define SPI_CLOCK_DIV16  0x04
#define SPI_CLOCK_DIV32  0x05
#define SPI_CLOCK_DIV64  0x06
#define SPI_CLOCK_DIV128 0x07

#define INPUT 0
#define OUTPUT 1
#define SPI 2

#define GPIO_MODE_PATH "/sys/devices/virtual/misc/gpio/mode/"
#define GPIO_FILENAME "gpio"

void writeFile(int fileID, int value);
void setPinMode(int pinID, int mode);
void configurePins(void);

#endif