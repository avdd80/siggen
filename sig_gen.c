#include <wiringPi.h>
#include <stdio.h>
#include "cos_wave.h"

#define UPRAMP    1
#define DOWNRAMP -1
#define TRIANGLE_WAVE_PEAK 1024
#define MY_PI  3.14159265358979
#define MY_2PI 6.28318530717958

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

/* Returns the closest cosine value. Phase in degrees */
int get_cosine_val (float phase)
{
	int phase_sampled = (int) (phase * 1024 / 360);
	phase_sampled %= 1024;
	if (phase_sampled < 0)
	{
		phase_sampled += 1024;
	}
	
	if (phase_sampled > 1023)
	{
		printf ("Bad phase value");
		exit (1);
	}
	
	return cosine_val[phase_sampled];
}

main ()
{
	unsigned int counter = 0;
	setup ();

	while (1)
	{
		pwm_val = get_cosine_val (counter);
		pwmWrite (1, pwm_val);
		delayMicroseconds ((unsigned int) 53333);
		counter++;
		counter %= 360;
		printf ("\n%d", pwm_val);
	}
	
	return 0;
}