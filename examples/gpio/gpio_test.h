#ifndef __gpio_test_h__
#define __gpio_test_h__

void writeFile(int fileID, int value);
void setPinMode(int pinID, int mode);
void setPin(int pinID, int state);

// Make some aliases to make the code more readable.
#define HIGH '1'
#define LOW  '0'

#define INPUT  '0'
#define OUTPUT '1'
#define INPUT_PU '8'

#endif