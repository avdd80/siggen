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

int cosine_basis_symbol[SYMBOLS_PER_SUBFRAME * SAMPLES_PER_SYMBOL];
int sine_basis_symbol[SYMBOLS_PER_SUBFRAME * SAMPLES_PER_SYMBOL];
int qpsk_pi_4  [SYMBOLS_PER_SUBFRAME * SAMPLES_PER_SYMBOL];
int qpsk_3pi_4 [SYMBOLS_PER_SUBFRAME * SAMPLES_PER_SYMBOL];
int qpsk_5pi_4 [SYMBOLS_PER_SUBFRAME * SAMPLES_PER_SYMBOL];
int qpsk_7pi_4 [SYMBOLS_PER_SUBFRAME * SAMPLES_PER_SYMBOL];

void gen_qpsk_symbols (int two_bit_data_packet);

int main ()
{
	gen_qpsk_symbols (2);
	return 0;
}

void gen_qpsk_symbols (int two_bit_data_packet)
{
	int i;
	/* Generate sine and cosine basis symbols */
	generate_basis_symbol (SYMBOLS_PER_SUBFRAME * SAMPLES_PER_SYMBOL, cosine_basis_symbol, 0);
	generate_basis_symbol (SYMBOLS_PER_SUBFRAME * SAMPLES_PER_SYMBOL, sine_basis_symbol, 270);
	
	for (i = 0; i < SYMBOLS_PER_SUBFRAME * SAMPLES_PER_SYMBOL; i++)
	{
		qpsk_pi_4[i]  = (cosine_basis_symbol[i] + sine_basis_symbol[i])   >> 1;
		qpsk_3pi_4[i] = (sine_basis_symbol[i]   - cosine_basis_symbol[i]) / 2;
		qpsk_5pi_4[i] = -1 * ((cosine_basis_symbol[i] + sine_basis_symbol[i]) >> 1);
		qpsk_7pi_4[i] = (cosine_basis_symbol[i] - sine_basis_symbol[i])/2;
	}
	
	for (i = 0; i < SYMBOLS_PER_SUBFRAME * SAMPLES_PER_SYMBOL; i++)
	{
		printf ("\n%d", qpsk_pi_4[i]);
		//qpsk_3pi_4[i] = (sine_basis_symbol[i]   - cosine_basis_symbol[i]) / 2;
		//qpsk_5pi_4[i] = -1 * ((cosine_basis_symbol[i] + sine_basis_symbol[i]) >> 1);
		//qpsk_7pi_4[i] = (cosine_basis_symbol[i] - sine_basis_symbol[i])/2;
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