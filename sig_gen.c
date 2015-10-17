#include <wiringPi.h>

#define UPRAMP    1
#define DOWNRAMP -1
#define TRIANGLE_WAVE_PEAK 0xFFF

int pwm_val = 0;
int ramp_direction = UPRAMP;
int scale = 4095;

while (1)
{
	if (!pwm_val)
	{
		ramp_direction = UPRAMP;
	}
	else if (pwm_val == TRIANGLE_WAVE_PEAK)
	{
		ramp_direction = DOWNRAMP;
	}
	
	if (!scale)
	{
		--scale;
	}
	else
	{
		scale = 4095;
		pwm_val += ramp_direction;
	}
}