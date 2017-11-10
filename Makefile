# Makefile for 360 Project

GCC = gcc -pedantic -std=c11
LIBS = -lm
FLAGS = -Wall
ALGODIR = prng_algos
LIBSDIR = prng_libs

libourprng: $(ALGODIR)/xorshift.c
	$(GCC) $(FLAGS) -c -o $(ALGODIR)/xorshift.o -fPIC $(ALGODIR)/xorshift.c $(LIBS)
	$(GCC) $(FLAGS) -shared -o libourprng.so $(ALGODIR)/xorshift.o $(LIBS)

runner: libourprng prng_runner.c
	$(GCC) $(FLAGS) -o runner.exec prng_runner.c -L/Users/Ameha/Desktop/gifan/360_stuff -lourprng $(LIBS)

write-nums: runner
	./runner.exec
