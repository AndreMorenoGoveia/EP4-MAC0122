CC=gcc
CFlags=-Wall -ansi -pedantic -O2


all: ep4


ep4: ep4.o
	$(CC) $(CFlags) ep4.o


ep4.o: ep4.c
	$(CC) $(CFlags) -c ep4.c



clean:
	rm *.o