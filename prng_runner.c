#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include "libourprng.h"

int main(int argc, char** argv)
{
    double nrandnums = pow(2, 16);
    uint32_t seed = 1000;

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
                    xorshift32(&seed));
        }
    }
}
