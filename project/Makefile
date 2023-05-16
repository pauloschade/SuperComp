#compile all files in helpers folder
DFFLAGS = -Wall -O3 -g
STDFLAG = -std=c++17
CFLAGS = $(DFFLAGS)
CC = g++
#g++-12
#g++ -Wall -O3 -g file.cpp -o file

#make main.cpp at guloso folder
.PHONY: guloso
guloso: build
	$(CC) $(CFLAGS) -o guloso guloso.cpp *.o

.PHONY: aleatorio
aleatorio: build
	$(CC) $(CFLAGS) -o aleatorio aleatorio.cpp *.o

.PHONY: exaustivo
exaustivo: build
	$(CC) $(CFLAGS) -o exaustivo exaustivo.cpp *.o


.PHONY: exaust
exaust: build
	$(CC) $(CFLAGS) -o exaust exaust.cpp *.o

#make exaustivo_omp
.PHONY: exaustivo_omp
exaustivo_omp: build
	$(CC) $(CFLAGS) -fopenmp -o exaustivo_omp exaustivo_omp.cpp *.o



.PHONY: build
build:
	$(CC) $(CFLAGS) -c helpers/*.cpp

.PHONY: generator
generator:
	$(CC) $(CFLAGS) -o gen generator/generator.cpp

.PHONY: clean
clean:
	rm -f *.o *.gch *.out guloso aleatorio gen exaustivo exaustivo_omp
	rm -rf generator/*.dSYM *.dSYM