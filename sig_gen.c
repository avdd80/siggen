#include <wiringPi.h>
#include <stdio.h>
#include <math.h>
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

/* Returns the closest cosine value from a LUT. angle in degrees */
int get_cosine_val (int angle)
{
	
	angle %= 360;
	if (angle < 0)
	{
		angle += 360;
	}
	
	if (angle > 359)
	{
		printf ("Bad angle value");
		exit (1);
	}
	
	return cosine[angle];
}

main ()
{
	unsigned int counter = 0;
	setup ();

	while (1)
	{
		pwm_val = get_cosine_val (counter);
		pwmWrite (1, pwm_val);
		
		/* Add a delay of 1/360 seconds between two samples */
		delayMicroseconds ((unsigned int) 2778);
		counter++;
		counter %= 360;
		//printf ("\n%d", pwm_val);
	}
	
	return 0;
}