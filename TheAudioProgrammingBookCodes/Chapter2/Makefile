# Author: LucasPacheco

################################
#Just modify the Listing number
LISTING = 2.1.3#
################################

# Folders Flags
SRC     = ../Resources/portsf
INCLUDE = "../Resources/include"

# Command Flags
CC      = gcc
OBJFLAG = -c
EXEFLAG = -o
HS_FLAG = -I
MTHFLAG = -lm

all:
	$(CC) $(OBJFLAG) $(SRC)/portsf.c $(HS_FLAG) $(INCLUDE)
	$(CC) $(OBJFLAG) $(SRC)/ieee80.c 
	$(CC) $(OBJFLAG) Listing$(LISTING).c $(HS_FLAG) $(INCLUDE)
	$(CC) $(EXEFLAG) ex Listing$(LISTING).o ieee80.o portsf.o $(MTHFLAG)

run:


clean:
	rm ./*.o
	clear

cleanAll:
	rm ./*.o
	rm ex
	clear