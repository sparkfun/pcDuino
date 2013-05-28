/***************************************************************************
analog.cpp

Example code for analog I/O access on the pcDuino via C++.

26 Mar 2013 - Mike Hord, SparkFun Electronics

This code is beerware- if you find it useful, please buy me (or, for that
matter, any other SparkFun employee you met) a pint next time you meet us at
the local.

***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "analog.h"

int adc[6];     // Array for file descriptors for the adc pins
int PWMMaxVal[6]; // Store the max values for the PWM outputs
char path[64];  // Nice big buffer for constructing file paths

int main(void)
{
  // For starters, let's create file descriptors for all the ADC pins. PWM is
  //   handled differently; see the analogWrite() function for details.
	for(int i = 0; i<= 5; i++)
	{
		memset(path, 0, sizeof(path));
		sprintf(path, "%s%s%d", ADC_IF_PATH, ADC_IF_FILE , i);
		adc[i] = open(path, O_RDONLY);
		memset(path, 0, sizeof(path));
		sprintf(path, "%s%s%d/%s", PWM_IF_PATH, PWM_IF_FILE , i, PWM_MAX);
		int PWMMaxFD = open(path, O_RDONLY);
		char PWMMaxStr[4];
		read(PWMMaxFD, PWMMaxStr, sizeof(PWMMaxStr));
		PWMMaxVal[i] = atoi(PWMMaxStr);
	}

  // Now, we'll blast all the PWM pins to zero. 
  for(int j = 0; j<=5; j++)
  {
    analogWrite(j, 0);
  }
  
  // Now we can go about the business of dimming some LEDs. 
  for(int j = 0; j<=5; j++)
  {
    for(int i = 0; i<=255; i++)
    {
      analogWrite(j, i);
      usleep(10000);
    }
    analogWrite(j, 0);
  }
  
  // Analog input is handled by file streams.
  for (int i = 0; i <= 5; i++)
  {
    char ADCBuffer[16];
    lseek(adc[i], 0, SEEK_SET);
    int res = read(adc[i], ADCBuffer, sizeof(ADCBuffer));
    int ADCResult = atoi(ADCBuffer);
    printf("ADC Channel: %d Value: %s", i, ADCBuffer);
  }
}

  // PWM pin access is handled by
  //   using the system() command to invoke the command process to execute a
  //   command. We assemble the command using sprintf()- the command takes
  //   the form
  //   echo <value> > /sys/class/leds/pwmX/brightness
  //   where <value> should be replaced by an integer from 0-255 and X should
  //   be replaced by an index value from 0-5
void analogWrite(int pin, int value)
{
  memset(path, 0, sizeof(path));
  value = (PWMMaxVal[pin] * value)/255;
  sprintf(path, "echo %d > %s%s%d/%s", value, PWM_IF_PATH, PWM_IF_FILE, \
    pin, PWM_IF);
  system(path);
}