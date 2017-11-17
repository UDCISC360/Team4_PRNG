#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include "libourprng.h"

double nrandnums = 65536;
uint32_t xorshift32_seed = 1000;

uint32_t lag1 = 5;
uint32_t lag2 = 17;
uint32_t modval = 4294967296;
uint32_t initvals[] = {2, 3, 5, 7, 11, 13, 17, 19, 23,
                       29, 31, 37, 41, 43, 47, 53, 59};

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
                    xorshift32(xorshift32_seed));
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
                    lfg(lag1, lag2, modval, initvals));
        }
    }

    lfg_free();
}

int main(int argc, char** argv)
{
    //test_xorshift32();
    test_lfg();
}
