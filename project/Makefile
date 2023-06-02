#compile all files in helpers folder
DFFLAGS = -Wall -O3 -g
STDFLAG = -std=c++17
CFLAGS = $(DFFLAGS) $(STDFLAG)
#CC = g++
CC = g++-12
CCN = g++

CGPU = nvcc -arch=sm_70 -std=c++14
#g++ -Wall -O3 -g file.cpp -o file

#make main.cpp at guloso folder
.PHONY: guloso
guloso: build
	$(CC) $(CFLAGS) -o guloso guloso.cpp *.o

.PHONY: aleatorio
aleatorio: build
	$(CC) $(CFLAGS) -o aleatorio aleatorio.cpp *.o

#make exaustivo_omp
.PHONY: exaustivo_omp
exaustivo_omp: build
	$(CC) $(CFLAGS) -fopenmp -o exaustivo_omp exaustivo_omp.cpp *.o

.PHONY: exaustivo_gpu
exaustivo_gpu: build
	$(CGPU) -o exaustivo_gpu exaustivo_gpu.cu *.o

.PHONY: exaustivo_gpu_red
exaustivo_gpu_red: build
	$(CGPU) -o exaustivo_gpu_red exaustivo_gpu.cu *.o

.PHONY: exaustivo
exaustivo: build
	$(CC) $(CFLAGS) -o exaustivo exaustivo.cpp *.o


.PHONY: build
build:
	$(CC) $(CFLAGS) -c helpers/*.cpp

.PHONY: generator
generator:
	$(CC) $(CFLAGS) -o gen generator/generator.cpp

.PHONY: clean
clean:
	rm -f *.o *.gch *.out guloso aleatorio gen exaustivo exaustivo_omp exaustivo_gpu exaustivo_gpu_red
	rm -rf generator/*.dSYM *.dSYM