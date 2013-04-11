/***************************************************************************
analog.h

Header file for analog I/O access on the pcDuino via C++.

26 Mar 2013 - Mike Hord, SparkFun Electronics

This code is beerware- if you find it useful, please buy me (or, for that
matter, any other SparkFun employee you met) a pint next time you meet us at
the local.

***************************************************************************/

#ifndef __analog_h__
#define __analog_h__

#define PWM_IF_PATH "/sys/class/leds/"
#define PWM_IF_FILE "pwm"
#define PWM_IF "brightness"
#define PWM_MAX "max_brightness"

#define ADC_IF_PATH "/proc/"
#define ADC_IF_FILE "adc"

void analogWrite(int pin, int value);

#endif