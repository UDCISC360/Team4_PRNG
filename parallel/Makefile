CC = cc -std=c11
NVCC = nvcc
MPICC = mpicc -std=c11 -lm
HOST := $(shell hostname)
ifeq ($(HOST),cisc372)
RUN = srun -n 1
MPIRUN = srun
OMPRUN = srun -n 1 -c 40
LIBS = 
FLAGS = -Xcompiler -fopenmp
else
RUN = 
MPIRUN = mpiexec
OMPRUN = 
LIBS = 
FLAGS = -I/opt/local/include -L/opt/local/lib 
FFMPEG = ffmpeg
endif


######################### Parallel Version #########################

cudaonly.exe: lfgpar_cuda.cu Makefile
	$(NVCC) -o cudaonly.exe $(FLAGS) lfgpar_cuda.cu $(LIBS)

cudaonly: cudaonly.exe
	$(RUN) --gres=gpu:1 ./cudaonly.exe

hybrid.exe: lfgpar_hybrid.cu Makefile
	$(NVCC) -o hybrid.exe $(FLAGS) lfgpar_hybrid.cu $(LIBS)

hybrid: hybrid.exe
	$(OMPRUN) --gres=gpu:1 ./hybrid.exe

mpionly.exe: lfgpar_mpi.c Makefile
	$(MPICC) -o mpionly.exe lfgpar_mpi.c $(LIBS) -lm

mpionly: mpionly.exe
	$(MPIRUN) -n 3 ./mpionly.exe

seq.exe: lfg.c Makefile
	$(CC) -o seq.exe lfg.c $(LIBS)

seq: seq.exe
	$(RUN) ./seq.exe

clean:
	rm -f *.mp4 *.exe a.out *.o *~ \#*\#
