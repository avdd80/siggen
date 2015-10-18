/***************************************************************************
* FUNCTION  get_consine_value
* 
* Description
*
* Returns the consine value of an angle specified in degrees
*
***************************************************************************/
#include "common.h"
#include "cosine.h"
#include <math.h>

void generate_basis_symbol (int number_of_samples, int* symbol_ptr, int phase)
{
	int sample_index = (int) round (phase * (SAMPLES_PER_SYMBOL / 360));
	
	while (!number_of_samples)
	{
		*symbol_ptr = cosine_wave [sample_index];
		
		sample_index++;
		sample_index %= 32;
		--number_of_samples;		
	}
}