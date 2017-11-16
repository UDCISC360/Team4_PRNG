#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdint.h>

int a = 1664525;
int c = 1013904223;

uint32_t lcg(uint32_t seed){
  return (a * seed + c) & 0xFFFFFFFF;
}
int main(){
  uint32_t count = 0;
  uint32_t seed = lcg(0);
  while(seed != 0 || count == 0){
    printf("%u\n", seed);
    seed = lcg(seed);
    //sleep(1);
    count++;
    //if((count & 0x0FFFFFFF) == 0) printf("lcg[%u] = %u\n", count, seed);
  }
  //printf("wuh oh! period is %u\n", count);
  return 0;
}
