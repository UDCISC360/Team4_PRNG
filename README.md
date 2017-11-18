# OSX/LINUX INSTRUCTIONS:

1. Open the working directory in a terminal.
2. Type `pwd` in the terminal. Note the returned address.
3. Open up Makefile in a text editor.
4. At the top of the file change the CWD variable to the output of step 2.
5. Type `make libourprng` in the terminal.
6. Type `make runner` in the terminal. At this point you have a working
   binary.
7. To run the code type `./runner.exe prng testarg` where prng is one of {xorshift,
   lcg, lfg, twister} and testarg is one of {test, notest}. The prng argument
   tells the driver program which algorithm to generate random numbers with.
   The testarg argument tells the driver to output 2^16 random numbers if it
   is "test." If it is "notest", then the driver will generate 2^32 random
   numbers with no output at all.

