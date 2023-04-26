#compile all files in helpers folder
DFFLAGS = -Wall -O3 -g
STDFLAG = -std=c++17
CFLAGS = $(DFFLAGS) $(STDFLAG)
CC = g++

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

.PHONY: build
build:
	$(CC) $(CFLAGS) -c helpers/*.cpp

.PHONY: generator
generator:
	$(CC) $(CFLAGS) -o gen generator/generator.cpp

.PHONY: clean
clean:
	rm -f *.o *.gch *.out guloso aleatorio gen
	rm -rf generator/*.dSYM *.dSYM