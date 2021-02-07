# Author: LucasPacheco

################################
#Just modify the Listing number
LISTING = 2.1.6#
################################

# Folders Flags
SRC1     = ../Resources/portsf
SRC2     = ../Resources/breakpoints
INCLUDE1 = ../Resources/include
INCLUDE2 = ../Resources/breakpoints/include

# Command Flags
CC      = gcc
OBJFLAG = -c
EXEFLAG = -o
HS_FLAG = -I
MTHFLAG = -lm

all:
	$(CC) $(OBJFLAG) $(SRC1)/portsf.c $(HS_FLAG) $(INCLUDE1)
	$(CC) $(OBJFLAG) $(SRC1)/ieee80.c 
	$(CC) $(OBJFLAG) $(SRC2)/breakpoints.c $(HS_FLAG) $(INCLUDE2)
	$(CC) $(OBJFLAG) Listing$(LISTING).c $(HS_FLAG) $(INCLUDE1) $(HS_FLAG) $(INCLUDE2)
	$(CC) $(EXEFLAG) ex Listing$(LISTING).o ieee80.o portsf.o breakpoints.o $(MTHFLAG)

run:


clean:
	rm ./*.o
	clear

cleanAll:
	rm ./*.o
	rm ex
	clear