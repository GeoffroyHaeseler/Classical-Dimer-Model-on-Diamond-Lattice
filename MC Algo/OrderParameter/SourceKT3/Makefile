# Makefile for Writing Make Files Example
 
# *****************************************************
# Variables to control Makefile operation
 
CC = g++
CFLAGS = -Wall -g
 
# ****************************************************
# Targets needed to bring the executable up to date
 
KT3: addAWorm.o defs.o growTheWorm.o initialise.o main.o measure.o next.o nspFunctions.o
	$(CC) $(CFLAGS) -o KT3 main.o addAWorm.o defs.o growTheWorm.o initialise.o measure.o next.o nspFunctions.o
 
# The main.o target can be written more simply
 
main.o: addAWorm.o defs.o initialise.o measure.o
	$(CC) $(CFLAGS) -c main.cpp
 
addAWorm.o: addAWorm.h defs.h check.o growTheWorm.h

defs.o: defs.h

growTheWorm.o: defs.h growTheWorm.h next.h

initialise.o: defs.h initialise.h nspFunctions.h

measure.o: defs.h measure.h nspFunctions.h

next.o: defs.h next.h

nspFunctions.o: defs.h nspFunctions.h

