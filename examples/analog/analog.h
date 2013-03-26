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