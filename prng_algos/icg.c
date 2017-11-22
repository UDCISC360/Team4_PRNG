#include <stdint.h>
/*
 * This function calculates the modular multiplicative inverse.
 * In particular it finds x such that
 *     (state)x + (modval)y = 1
 * The function implements the Extended Euclidean Algorithm.
 */
uint32_t mul_inv(uint32_t prev_remain, uint32_t curr_remain)
{
	uint32_t modval_orig = curr_remain;
	uint32_t temp;
	uint32_t curr_quot;
	uint32_t curr_inverse = 0;
	uint32_t prev_inverse = 1;
	
	if (curr_remain == 1)
    {		
		return 1;
	}
	
	while (prev_remain > 0)
	{
		curr_quot = prev_remain / curr_remain;
		
		temp = curr_remain;
		curr_remain = prev_remain % curr_remain;
		prev_remain = temp;
		
		temp = curr_inverse;
		curr_inverse = prev_inverse - curr_quot * curr_inverse;
		prev_inverse = temp;
	}
	
	if (prev_inverse < 0)
	{
		prev_inverse += modval_orig;
	}
	
	return prev_inverse;
}

/*
 * The Inverse Congruential Generator has a state that is given by an integer.
 * Each state corresponds to a different random number. The algorithm changes state
 * by calculating:
 *     new_state = ((multfactor * state^-1) + addfactor) mod modval
 * Note that state^-1 refers to the modular multiplicative inverse of state
 * with respect to modval. It is given by finding x such that
 *     (state)x + (modval)y = 1
 * NOTE: modval should be a prime number
 */
uint32_t icg(uint32_t* state, uint32_t* modval, uint32_t* multfactor,
             uint32_t* addfactor)
{
	if(*state == 0)
	{
		return *addfactor;
	}
	else
	{
		uint32_t inverse = mul_inv(*state, *modval);
		return ((inverse * (*multfactor)) + *addfactor) % *modval;
	}
}
