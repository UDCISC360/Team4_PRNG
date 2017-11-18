# Makefile for 360 Project

# Check for windows system enviornment variable
ifdef SYSTEMROOT
else
   ifeq ($(shell uname), Linux)
   endif
endif

MINGW = x86_64-w64-mingw32-gcc -pedantic -std=c11
GCC = gcc -pedantic -std=c11
MINGW-AR = x86_64-w64-mingw32-gcc-ar rcs
AR = ar rcs
LIBS = -lm
FLAGS = -Wall
ALGODIR = prng_algos
LIBSDIR = prng_libs
CWD = "/home/gifan/Resources/Data/School Stuff/College/Cisc 360/project/CISC360-Project"

libourprngwin: $(ALGODIR)/xorshift.c $(ALGODIR)/lfg.c $(ALGODIR)/lcg.c libourprng.h
	$(MINGW) $(FLAGS) -c -o $(ALGODIR)/xorshift.o -fPIC $(ALGODIR)/xorshift.c $(LIBS)
	$(MINGW) $(FLAGS) -c -o $(ALGODIR)/lfg.o -fPIC $(ALGODIR)/lfg.c $(LIBS)
	$(MINGW) $(FLAGS) -c -o $(ALGODIR)/lcg.o -fPIC $(ALGODIR)/lcg.c $(LIBS)
	$(MINGW-AR) -o libourprngwin.a $(ALGODIR)/xorshift.o $(ALGODIR)/lfg.o $(ALGODIR)/lcg.o

libourprng: $(ALGODIR)/xorshift.c $(ALGODIR)/lfg.c $(ALGODIR)/lcg.c libourprng.h
	$(GCC) $(FLAGS) -c -o $(ALGODIR)/xorshift.o -fPIC $(ALGODIR)/xorshift.c $(LIBS)
	$(GCC) $(FLAGS) -c -o $(ALGODIR)/lfg.o -fPIC $(ALGODIR)/lfg.c $(LIBS)
	$(GCC) $(FLAGS) -c -o $(ALGODIR)/lcg.o -fPIC $(ALGODIR)/lcg.c $(LIBS)
	$(AR) libourprng.a $(ALGODIR)/xorshift.o $(ALGODIR)/lfg.o $(ALGODIR)/lcg.o

runnerwin: libourprngwin prng_runner.c
	$(MINGW) $(FLAGS) -o runnerwin.exe prng_runner.c -L$(CWD) -lourprngwin $(LIBS)

runner: libourprng prng_runner.c
	$(GCC) $(FLAGS) -o runner.exe prng_runner.c -L$(CWD) -lourprng $(LIBS)

full-compile: runnerwin runner

test-xorshift: runner
	./runner.exe xorshift test

test-lfg: runner
	./runner.exe lfg test

test-lcg: runner
	./runner.exe lcg test

test-twister: runner
	./runner.exe twister test

experiment-xorshift: runner
	./runner.exe xorshift notest

experiment-lfg: runner
	./runner.exe lfg notest

experiment-lcg: runner
	./runner.exe lcg notest

experiment-twister: runner
	./runner.exe twister notest
