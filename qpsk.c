#include <stdio.h>
#include "cosine.h"
#include "common.h"

/*
QPSK symbol mapping

                    |
      01            |            11
       x            |            x
                    |
                    |
                    |
--------------------+--------------------
                    |
                    |
                    |
       x            |            x
      00            |            10
                    |
*/
/***************************************************************************
* FUNCTION  generate_basis_symbol
* 
* Description
*
* Repeat samples to generate a signal of specified number of samples
*
***************************************************************************/

#include <stdio.h>
#include "common.h"
#include "cosine.h"

int cosine_basis_symbol[SAMPLES_PER_SUBFRAME];
int sine_basis_symbol[SAMPLES_PER_SUBFRAME];
int qpsk_1pi_4  [SAMPLES_PER_SUBFRAME];
int qpsk_3pi_4 [SAMPLES_PER_SUBFRAME];
int qpsk_5pi_4 [SAMPLES_PER_SUBFRAME];
int qpsk_7pi_4 [SAMPLES_PER_SUBFRAME];

void gen_qpsk_symbols (int two_bit_data_packet);

void generate_basis_symbol (int number_of_samples, int* symbol_ptr, int phase)
{
	int sample_index = (int) round (phase * (SAMPLES_PER_SYMBOL / 360));
	
	//printf ("\nEntered basis sym num_samples=%d, cos[%d] = %d", number_of_samples, cosine_wave [sample_index], sample_index);
	while (number_of_samples)
	{
		*symbol_ptr = cosine_wave [sample_index];
		//printf ("\n%d", *symbol_ptr);
		sample_index++;
		sample_index %= 32;
		symbol_ptr++;
		--number_of_samples;		
	}
}

int main ()
{
	gen_qpsk_symbols (2);
	return 0;
}


void gen_qpsk_symbols (int two_bit_data_packet)
{
	int i;
	/* Generate sine and cosine basis symbols */
	generate_basis_symbol (15*32, cosine_basis_symbol, 0);
	generate_basis_symbol (SAMPLES_PER_SUBFRAME, sine_basis_symbol, 270);
	
	for (i = 0; i < SAMPLES_PER_SUBFRAME; i++)
	{
		qpsk_pi_4[i]  = (cosine_basis_symbol[i] + sine_basis_symbol[i])   >> 1;
		qpsk_3pi_4[i] = (sine_basis_symbol[i]   - cosine_basis_symbol[i]) / 2;
		qpsk_5pi_4[i] = -1 * ((cosine_basis_symbol[i] + sine_basis_symbol[i]) >> 1);
		qpsk_7pi_4[i] = (cosine_basis_symbol[i] - sine_basis_symbol[i])/2;
	}

	for (i = 0; i < SAMPLES_PER_SUBFRAME; i++)
	{
		qpsk_1pi_4[i] = (sine_basis_symbol[i]   + cosine_basis_symbol[i]) >> 1;
		qpsk_3pi_4[i] = (sine_basis_symbol[i]   - cosine_basis_symbol[i]) / 2;
		qpsk_5pi_4[i] = -1 * ((cosine_basis_symbol[i] + sine_basis_symbol[i]) >> 1);
		qpsk_7pi_4[i] = (cosine_basis_symbol[i] - sine_basis_symbol[i])/2;
		
		printf ("\n%d", qpsk_3pi_4[i]);
	}
	
	return;
}
/*
	if (two_bit_data_packet > 3 || two_bit_data_packet < 0 )
	{
		exit ();
	}
	switch (two_bit_data_packet):
	{
		case 0:
		return cosine + 
	}
}
*/