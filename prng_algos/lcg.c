#include <stdio.h>
#include <math.h>
#include <unistd.h>

int a = 1664525;
int c = 1013904223;

unsigned int lcg(unsigned int seed){
  return (a * seed + c) & 0xFFFFFFFF;
}
int main(){
  unsigned int count = 0;
  unsigned int seed = lcg(0);
  while(seed != 0 || count == 0){
    //printf("%u\n", seed);
    seed = lcg(seed);
    //sleep(1);
    count++;
    //if((count & 0x0FFFFFFF) == 0) printf("lcg[%u] = %u\n", count, seed);
  }
  printf("wuh oh! period is %u\n", count);
  return 0;
}
