#include <wiringPi.h>
#include <stdio.h>

#define UPRAMP    1
#define DOWNRAMP -1
#define TRIANGLE_WAVE_PEAK 1024

int pwm_val = 0;
int ramp_direction = UPRAMP;
long int scale = 2^18;

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
		
		if (!scale)
		{
			--scale;
		}
		else
		{
			scale = 2^14;
			pwm_val += ramp_direction;
			pwmWrite (1, pwm_val);
			printf ("\n%d", pwm_val);
		}
	}
	
	return 0;
}