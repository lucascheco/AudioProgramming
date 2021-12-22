# Author: LucasPacheco
# My template for makefiles

################################
PROGRAM = find_peak#
################################

# Folders Flags
SRC     = ../../Resources/portsf
INCLUDE = "../../Resources/include"

# Command Flags
CC      = gcc
OBJFLAG = -c
EXEFLAG = -o
HS_FLAG = -I
MTHFLAG = -lm

all:
	$(CC) $(OBJFLAG) $(SRC)/portsf.c $(HS_FLAG) $(INCLUDE)
	$(CC) $(OBJFLAG) $(SRC)/ieee80.c 
	$(CC) $(OBJFLAG) $(PROGRAM).c $(HS_FLAG) $(INCLUDE)
	$(CC) $(EXEFLAG) ../bin/$(PROGRAM) $(PROGRAM).o ieee80.o portsf.o $(MTHFLAG)
	rm ./*.o

run:
	

clean:
	rm ./*.o
	clear

cleanAll:
	rm ./*.o
	rm ex
	clear
