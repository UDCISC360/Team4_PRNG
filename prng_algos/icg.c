#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

uint32_t m = 2147483647;
uint32_t b = 71499791;
uint32_t a = 21916;

uint32_t mul_inv(uint32_t a, uint32_t b)
{
	uint32_t b0 = b, t, q;
	uint32_t x0 = 0, x1 = 1;
	if (b == 1) return 1;
	while (a > 1) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}

uint32_t icg(uint32_t seed){
  return mul_inv(seed, m) * a + b;
}
 
int main(void) {
	uint32_t num = icg(0);
	while(1){
	  printf("%llu\n", (unsigned long long)num);
	  num = icg(num);
	  sleep(1);
	}
	return 0;
}
