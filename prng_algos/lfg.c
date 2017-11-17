#include <stdlib.h>
#include <stdint.h>

static uint32_t lag1 = 0;
static uint32_t lag2 = 0;
static uint32_t modval = 0;
static uint32_t* state;

/* NOTE: seedlag1 should be less than seedlag2
 *       seedmodval should be a power of 2
 *       initvals should be an array with seedlag2 elements
 */
uint32_t lfg(uint32_t seedlag1, uint32_t seedlag2, uint32_t seedmodval,
             uint32_t initvals[])
{
    if(lag1 == 0)
    {
        lag1 = seedlag1;
        lag2 = seedlag2;
        modval = seedmodval - 1;
        state = (uint32_t *) malloc(sizeof(uint32_t) * lag2);

        for(int i = 0; i < lag2; i++)
        {
            state[i] = initvals[i];
        }
    }

    uint32_t result = (state[lag2 - lag1] + state[0]) & modval;
    for(int i = 0; i < lag2; i++)
    {
        state[i] = state[i + 1];
    }

    state[lag2 - 1] = result;
    return result;
}

void lfg_free()
{
    free(state);
}
