#include <stdint.h>

/*
 * NOTE: Initial modval should be equal to a power of 2 minus 1
 */
uint32_t lcg(uint32_t* state, uint32_t* modval, uint32_t* multfactor,
             uint32_t* addfactor)
{
    *state = (((*multfactor) * (*state)) + *addfactor) & *modval;
    return *state;
}
