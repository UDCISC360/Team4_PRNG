#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include <string.h>
#include "libourprng.h"

unsigned long long nrandnums;
// Uses a power of 2 minus 1 since algorithms use bitwise and
// rather than the modulo operator.
uint32_t modval = 4294967296 - 1;

uint32_t lcg_seed = 1000;
uint32_t lcg_multfactor = 13425235;
uint32_t lcg_addfactor = 156674;

uint32_t xorshift32_seed = 1000;
uint32_t shift1 = 13;
uint32_t shift2 = 15;
uint32_t shift3 = 3;

uint32_t lag1 = 5;
uint32_t lag2 = 17;
uint32_t initvals[] = {2, 3, 5, 7, 11, 13, 17, 19, 23,
                       29, 31, 37, 41, 43, 47, 53, 59};

uint32_t twister_seed = 93653;
					   
uint32_t icg_seed = 1000;					   
uint32_t icg_multfactor = 71499791;
uint32_t icg_addfactor = 21916;
// Note that icg requires a prime value to mod by.
// 2^32 - 5) is the prime closest to 2^32
uint32_t icg_modval = 4294967291;

void test_prng(char* prng)
{
    FILE* filepntr;
    char* mode = "w";

    if(!strcmp(prng, "xorshift"))
    {
        printf("Generating %llu random numbers with xorshift32 \n",
               nrandnums);
        fflush(stdout);

        filepntr = fopen("xorshift_out.txt", mode);
        for(int i = 0; i < nrandnums; i++)
        {
            fprintf(filepntr, "%" PRIu32 "\n",
                    xorshift32(&xorshift32_seed, &shift1, &shift2, &shift3));
        }
    }
    else if(!strcmp(prng, "lfg"))
    {
        printf("Generating %llu random numbers with lfg \n", nrandnums);
        fflush(stdout);

        filepntr = fopen("lfg_out.txt", mode);
        for(int i = 0; i < nrandnums; i++)
        {
            fprintf(filepntr, "%" PRIu32 "\n",
                    lfg(&lag1, &lag2, &modval, initvals));
        }
    }
    else if(!strcmp(prng, "lcg"))
    {
        printf("Generating %llu random numbers with lcg \n", nrandnums);
        fflush(stdout);

        filepntr = fopen("lcg_out.txt", mode);
        for(int i = 0; i < nrandnums; i++)
        {
            fprintf(filepntr, "%" PRIu32 "\n",
                    lcg(&lcg_seed, &modval, &lcg_multfactor, &lcg_addfactor));
        }
    }
    else if(!strcmp(prng, "twister"))
    {
        printf("Generating %llu random numbers with twister \n", nrandnums);
        fflush(stdout);
		
		filepntr = fopen("twister_out.txt", mode);
        for(int i = 0; i < nrandnums; i++)
        {
            fprintf(filepntr, "%" PRIu32 "\n",
                    twister(&twister_seed));
        }
    }
	else if(!strcmp(prng, "icg"))
    {
        printf("Generating %llu random numbers with icg \n", nrandnums);
        fflush(stdout);
		
		filepntr = fopen("icg_out.txt", mode);
        for(int i = 0; i < nrandnums; i++)
        {
            fprintf(filepntr, "%" PRIu32 "\n",
                    icg(&icg_seed, &icg_modval, &icg_multfactor, &icg_addfactor));
        }
    }
	
	fclose(filepntr);
}

void experiment_prng(char* prng)
{
    if(!strcmp(prng, "xorshift"))
    {
        printf("Generating %llu random numbers with xorshift32 \n",
               nrandnums);
        fflush(stdout);

        for(unsigned long i = 0; i < nrandnums; i++)
        {
            xorshift32(&xorshift32_seed, &shift1, &shift2, &shift3);
        }
    }
    else if(!strcmp(prng, "lfg"))
    {
        printf("Generating %llu random numbers with lfg \n", nrandnums);
        fflush(stdout);

        for(unsigned long i = 0; i < nrandnums; i++)
        {
            lfg(&lag1, &lag2, &modval, initvals);
        }
    }
    else if(!strcmp(prng, "lcg"))
    {
        printf("Generating %llu random numbers with lcg \n", nrandnums);
        fflush(stdout);

        for(unsigned long i = 0; i < nrandnums; i++)
        {
            lcg(&lcg_seed, &modval, &lcg_multfactor, &lcg_addfactor);
        }
    }
    else if(!strcmp(prng, "twister"))
    {
        printf("Generating %llu random numbers with twister \n", nrandnums);
        fflush(stdout);
		
		for(unsigned long i = 0; i < nrandnums; i++)
        {
            twister(&twister_seed);
        }
    }
	else if(!strcmp(prng, "icg"))
    {
        printf("Generating %llu random numbers with icg \n", nrandnums);
        fflush(stdout);
		
        for(unsigned long i = 0; i < nrandnums; i++)
        {
            icg(&icg_seed, &icg_modval, &icg_multfactor, &icg_addfactor);
        }
    }
}

int main(int argc, char** argv)
{
    char* prng = argv[1];
    char* teststr = argv[2];

    if(!strcmp(teststr, "test"))
    {
        nrandnums = 65536;
        test_prng(prng);
    }
    else
    {
        nrandnums = 4294967296;
        experiment_prng(prng);
    }

    return 0;
}
