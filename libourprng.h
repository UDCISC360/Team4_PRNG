#ifndef LIBOURPRNG
#define LIBOURPRNG

uint32_t xorshift32(uint32_t seed);
uint32_t lfg(uint32_t seedlag1, uint32_t seedlag2, uint32_t seedmodval,
             uint32_t initvals[]);
void lfg_free();
#endif
