# AED 2018-2019, sem.2
# Makefile for Project 1st submission
#-----------------------------------------------------------------------
#   Compiler, Compiler Flags
CC = gcc
CFLAGS = -g -Wall -ansi -pedantic -lm


walker: pint.o funcs.o matriz.o
	$(CC) $(CFLAGS) -o walker pint.o funcs.o matriz.o

pint.o: pint.c funcs.h
	$(CC) -c $(CFLAGS) pint.c

funcs.o: funcs.c funcs.h
	$(CC) -c $(CFLAGS) funcs.c

matriz.o: matriz.c matriz.h
	$(CC) -c $(CFLAGS) matriz.c

# tests
t:  t1


t1:
	./walker t1016.puz

clean::
		rm -f .o core rm -f *.o core walker *~ .fuse *.moves *.zip



FILES = $(shell ls ../FINAL/*t5018.puz)

VALG = valgrind --leak-check=full

v:
		for F in ${FILES}; do ${VALG}  ./walker $${F} ; done;
