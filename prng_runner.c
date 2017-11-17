#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include "libourprng.h"

//long nrandnums = 33554432;
unsigned long nrandnums = 4294967296;
uint32_t modval = 4294967296 - 1;

uint32_t lcg_seed = 1000;
uint32_t multfactor = 13425235;
uint32_t addfactor = 156674;

uint32_t xorshift32_seed = 1000;
uint32_t shift1 = 13;
uint32_t shift2 = 15;
uint32_t shift3 = 3;

uint32_t lag1 = 5;
uint32_t lag2 = 17;
uint32_t initvals[] = {2, 3, 5, 7, 11, 13, 17, 19, 23,
                       29, 31, 37, 41, 43, 47, 53, 59};

void test_lcg()
{
   FILE* filepntr;
   char* mode = "w";

   // Code to output numbers for xorshift32
   filepntr = fopen("output_files/c_lcg_out.txt", mode);
   if (filepntr == NULL)
   {
       fprintf(stderr, "Can't open output file! \n");
       exit(1);
   }
   else
   {
       for(int i = 0; i < nrandnums; i++)
       {
           fprintf(filepntr, "%" PRIu32 "\n",
                   lcg(&lcg_seed, &modval, &multfactor, &addfactor));
       }
   }
}

void test_xorshift32()
{
    FILE* filepntr;
    char* mode = "w";

    // Code to output numbers for xorshift32
    filepntr = fopen("output_files/c_xorshift32_out.txt", mode);
    if (filepntr == NULL)
    {
        fprintf(stderr, "Can't open output file! \n");
        exit(1);
    }
    else
    {
        for(int i = 0; i < nrandnums; i++)
        {
            fprintf(filepntr, "%" PRIu32 "\n",
                    xorshift32(&xorshift32_seed, &shift1, &shift2, &shift3));
        }
    }
}

void test_lfg()
{
    FILE* filepntr;
    char* mode = "w";

    // Code to output numbers for xorshift32
    filepntr = fopen("output_files/c_lfg_out.txt", mode);
    if (filepntr == NULL)
    {
        fprintf(stderr, "Can't open output file! \n");
        exit(1);
    }
    else
    {
        for(int i = 0; i < nrandnums; i++)
        {
            fprintf(filepntr, "%" PRIu32 "\n",
                    lfg(&lag1, &lag2, &modval, initvals));
        }
    }
}

int main(int argc, char** argv)
{
    prng = argv[1];

    if(strcmp(prng, "xorshift"))
    {
        printf("Generating %l random numbers with xorshift32 \n",
               nrandnums);
        fflush(stdout);
        test_xorshift32();
    }

    if(strcmp(prng, "lfg"))
    {
        printf("Generating %l random numbers with lfg \n", nrandnums);
        fflush(stdout);
        test_lfg();
    }

    if(strcmp(prng, "lcg"))
    {
        printf("Generating %l random numbers with lcg \n", nrandnums);
        fflush(stdout);
        test_lcg();
    }
}
