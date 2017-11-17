# Makefile for 360 Project

# Check for windows system enviornment variable
ifdef SYSTEMROOT
else
   ifeq ($(shell uname), Linux)
   endif
endif

GCC = gcc -pedantic -std=c11
LIBS = -lm
FLAGS = -Wall
ALGODIR = prng_algos
LIBSDIR = prng_libs

libourprng: $(ALGODIR)/xorshift.c
	$(GCC) $(FLAGS) -c -o $(ALGODIR)/xorshift.o -fPIC $(ALGODIR)/xorshift.c $(LIBS)
	$(GCC) $(FLAGS) -c -o $(ALGODIR)/lfg.o -fPIC $(ALGODIR)/lfg.c $(LIBS)
	$(GCC) $(FLAGS) -shared -o libourprng.so $(ALGODIR)/xorshift.o $(ALGODIR)/lfg.o $(LIBS)

runner: libourprng prng_runner.c
	$(GCC) $(FLAGS) -o runner.exec prng_runner.c -L/Users/Ameha/Desktop/gifan/360_stuff -lourprng $(LIBS)

write-nums: runner
	./runner.exec
