#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define seed 0
#define j 5
#define k 17
unsigned int m = 0x7FFFFFFF;
unsigned int array[k];

unsigned int fib(){
  unsigned int result = (array[k - j] + array[0]) & m;
  for(int i = 1; i < k; i++) array[i-1] = array[i];
  array[k-1] = result;
  return result;
}
int main(){
  srand(seed);
  for(int i = 0; i < k; i++) array[i] = rand() & m;
  unsigned int num;
  while(1){
    printf("%u\n", num);
    num = fib();
    sleep(1);
  }
  return 0;
}
