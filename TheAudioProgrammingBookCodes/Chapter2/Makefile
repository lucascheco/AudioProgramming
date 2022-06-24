# Author: LucasPacheco

################################
#Just modify the Listing number
LISTING = 2.6.1_oscgen#
################################

# Folders Flags
SRC1     = ../Resources/portsf
SRC2     = ../Resources/breakpoints
SRC3     = ../Resources/wave
INCLUDE1 = ../Resources/include
INCLUDE2 = ../Resources/breakpoints/include
INCLUDE3 = ../Resources/wave/include

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
	$(CC) $(OBJFLAG) $(SRC3)/wave.c $(HS_FLAG) $(INCLUDE3)
	$(CC) $(OBJFLAG) Listing$(LISTING).c $(HS_FLAG) $(INCLUDE1) $(HS_FLAG) $(INCLUDE2) $(HS_FLAG) $(INCLUDE3)
	$(CC) $(EXEFLAG) ex Listing$(LISTING).o ieee80.o portsf.o breakpoints.o wave.o $(MTHFLAG)

run:


clean:
	rm ./*.o
	clear

cleanAll:
	rm ./*.o
	rm ex
	clear
