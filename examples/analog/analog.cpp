#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define PWM_IF_PATH "/sys/class/leds/"
#define PWM_IF_FILE "pwm"

#define ADC_IF_PATH "/proc/"
#define ADC_IF_FILE "adc"

int adc[6];
int pwm[6];
char path[64];

int main(void)
{
	for(int i = 0; i<= 5; i++)
	{
		memset(path, 0, sizeof(path));
		sprintf(path, "%s%s%d", ADC_IF_PATH, ADC_IF_FILE , i);
		adc[i] = open(path, O_RDONLY);
		memset(path, 0, sizeof(path));
    sprintf(path,  "%s%s%d", PWM_IF_PATH, PWM_IF_FILE , i);
    pwm[i] = open(path, O_RDWR);
	}
  
  char buf[32];
  read(adc[0], buf, sizeof(buf));
  printf("%s", buf);
}