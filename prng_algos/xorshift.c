#include <stdint.h>
#include <stdlib.h>

static uint32_t state = 0;

/* This xorshift32 function is a basic one taken from Wikipedia.
 * See https://en.wikipedia.org/wiki/Xorshift for more information.
 * With xorshift32 the state and seed are the same type. On
 * the first call, xorshift32 sets the initial state to be the seed value.
 * On continued calls the function cycles through states through a series
 * of bit shifts and XOR operations. The new state is the outputted random
 * number.
 * NOTE: seed must not be equal to 0
 */
uint32_t xorshift32(uint32_t seed)
{
    if(state == 0)
    {
        state = seed;
    }

	state ^= state << 13;
	state ^= state >> 17;
	state ^= state << 5;
	return state;
}
