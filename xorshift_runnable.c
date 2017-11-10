#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

uint32_t startState;

/* The state word must be initialized to non-zero */
uint32_t xorshift32(uint32_t state[static 1])
{
	/* Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs" */

	uint32_t x = state[0];
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	state[0] = x;
	return x;
}

int main(int argc, char** argv)
{
    startState = atoi(argv[1]);
    printf("Start state is %d \n", startState);
    for(int i = 0; i<100; i++)
    {
        printf("We got %" PRIu32 "\n", xorshift32(&startState));
    }
}
