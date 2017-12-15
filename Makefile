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
FLAGS = -Wall -g
ALGODIR = prng_algos
LIBSDIR = prng_libs
CWD = "/home/mike/Documents/CISC360/prng/repo"

libourprngwin: $(ALGODIR)/xorshift.c $(ALGODIR)/lfg.c $(ALGODIR)/lcg.c libourprng.h
	$(MINGW) $(FLAGS) -c -o $(ALGODIR)/xorshift.o -fPIC $(ALGODIR)/xorshift.c $(LIBS)
	$(MINGW) $(FLAGS) -c -o $(ALGODIR)/lfg.o -fPIC $(ALGODIR)/lfg.c $(LIBS)
	$(MINGW) $(FLAGS) -c -o $(ALGODIR)/lcg.o -fPIC $(ALGODIR)/lcg.c $(LIBS)
	$(MINGW) $(FLAGS) -c -o $(ALGODIR)/twister.o -fPIC $(ALGODIR)/twister.c $(LIBS)
	$(MINGW) $(FLAGS) -c -o $(ALGODIR)/icg.o -fPIC $(ALGODIR)/icg.c $(LIBS)
	$(MINGW-AR) -o libourprngwin.a $(ALGODIR)/xorshift.o $(ALGODIR)/lfg.o $(ALGODIR)/lcg.o $(ALGODIR)/twister.o $(ALGODIR)/icg.o

libourprng: $(ALGODIR)/xorshift.c $(ALGODIR)/lfg.c $(ALGODIR)/lcg.c libourprng.h
	$(GCC) $(FLAGS) -c -o $(ALGODIR)/xorshift.o -fPIC $(ALGODIR)/xorshift.c $(LIBS)
	$(GCC) $(FLAGS) -c -o $(ALGODIR)/lfg.o -fPIC $(ALGODIR)/lfg.c $(LIBS)
	$(GCC) $(FLAGS) -c -o $(ALGODIR)/lcg.o -fPIC $(ALGODIR)/lcg.c $(LIBS)
	$(GCC) $(FLAGS) -c -o $(ALGODIR)/twister.o -fPIC $(ALGODIR)/twister.c $(LIBS)
	$(GCC) $(FLAGS) -c -o $(ALGODIR)/icg.o -fPIC $(ALGODIR)/icg.c $(LIBS)
	$(AR) libourprng.a $(ALGODIR)/xorshift.o $(ALGODIR)/lfg.o $(ALGODIR)/lcg.o $(ALGODIR)/twister.o $(ALGODIR)/icg.o

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

test-icg: runner
	./runner.exe icg test

experiment-xorshift: runner
	./runner.exe xorshift notest

experiment-lfg: runner
	./runner.exe lfg notest

experiment-lcg: runner
	./runner.exe lcg notest

experiment-twister: runner
	./runner.exe twister notest
	
experiment-icg: runner
	./runner.exe twister notest

clean: Makefile
	rm *.exe */*.o *.a
