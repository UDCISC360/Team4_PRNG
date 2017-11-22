#include <stdint.h>

/*
 * The Lagged Fibonacci Generator has a state that is an array of lag2
 * elements. The state begins as initvals. To produce a new random number,
 * the function returns
 *     (state[lag2-lag1] + state[0]) mod modval
 * It then shift all the states left by 1 to add the new
 * values to the state values.
 * NOTE: lag1 should be less than lag2
 *       modval should be a power of 2 minus 1
 *       state should be an array with lag2 elements
 */
uint32_t lfg(uint32_t* lag1, uint32_t* lag2, uint32_t* modval,
             uint32_t* state)
{
    uint32_t result = (state[(*lag2) - (*lag1)] + state[0]) & *modval;
    for(int i = 0; i < *lag2; i++)
    {
        state[i] = state[i + 1];
    }

    state[*lag2 - 1] = result;
    return result;
}
