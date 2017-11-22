#ifndef LIBOURPRNG
#define LIBOURPRNG

uint32_t xorshift32(uint32_t* state, uint32_t* shift1, uint32_t* shift2,
                    uint32_t* shift3);

uint32_t lfg(uint32_t* lag1, uint32_t* lag2, uint32_t* modval,
             uint32_t* state);

uint32_t lcg(uint32_t* state, uint32_t* modval, uint32_t* multfactor,
             uint32_t* addfactor);
			 
uint32_t icg(uint32_t* state, uint32_t* modval, uint32_t* multfactor,
             uint32_t* addfactor);
#endif
