# Makefile for 360 Project

GCC = gcc -pedantic -std=c11
LIBS = -lm -lgd -pthread
FLAGS = -Wall
ALGODIR = prng_algos
LIBSDIR = prng_libs

libourprng: xorshift.c
	$(GCC) $(FLAGS) -c -fPIC $(ALGODIR)/xorshift.c
	$(GCC) $(FLAGS) -shared -o $(LIBSDIR)/libourprng.so $(ALGODIR)/xorshift.o
