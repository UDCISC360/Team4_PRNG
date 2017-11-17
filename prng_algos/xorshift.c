#include <stdint.h>
#include <stdlib.h>

/* This xorshift32 function is a basic one taken from Wikipedia.
 * See https://en.wikipedia.org/wiki/Xorshift for more information.
 * On continued calls, the xorshift32 cycles through states through a series
 * of bit shifts and XOR operations. The new state is the outputted random
 * number.
 * NOTE: Initial state must not be equal to 0.
 */
uint32_t xorshift32(uint32_t* state, uint32_t* shift1, uint32_t* shift2,
                    uint32_t* shift3)
{
	*state ^= *state << *shift1;
	*state ^= *state >> *shift2;
	*state ^= *state << *shift3;
	return *state;
}
