# AED 2018-2019, sem.2
# Makefile for Project 1st submission
#-----------------------------------------------------------------------
#   Compiler, Compiler Flags
CC = gcc
CFLAGS = -g -Wall -ansi -pedantic -lm


walker: pint.o funcs.o 
	$(CC) $(CFLAGS) -o walker pint.o funcs.o
	
pint: pint.c funcs.h
	$(CC) -c $(CFLAGS) pint.c

funcs.o: funcs.c funcs.h 
	$(CC) -c $(CFLAGS) funcs.c

# tests
t:  t1


t1:
	./walker t3008.puz0

clean::
	rm -f .o core a.out walker~


FILES = $(shell ls ../DEA-project-master/*t3008.puz0)

VALG = valgrind --leak-check=full

v:
	for F in ${FILES}; do ${VALG}  ./walker $${F} ; done;