#include <wiringPi.h>
#include <stdio.h>

#define UPRAMP    1
#define DOWNRAMP -1
#define TRIANGLE_WAVE_PEAK 1024

int pwm_val = 0;
int ramp_direction = UPRAMP;

void setup ()
{
	if (wiringPiSetup ())
	{
		exit (1);
	}
	pinMode (1, PWM_OUTPUT);
	
	return;
}

main ()
{
	setup ();

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
		
		pwm_val += ramp_direction;
		pwmWrite (1, pwm_val);
		delayMicroseconds ((unsigned int) 976);
	}
	
	return 0;
}