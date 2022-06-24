# Author: LucasPacheco

################################
#Just modify the exercise number
EXERCIS = 259#
################################

# Folders Flags
PSF     = ../Resources/portsf
BRK     = ../Resources/breakpoints
INCLUDE = "../Resources/include"
SRC3     = ../Resources/wave
INCLUDE3 = ../Resources/wave/include

# Command Flags
CC      = gcc
OBJFLAG = -c
EXEFLAG = -o
HS_FLAG = -I
MTHFLAG = -lm

all:
	$(CC) $(OBJFLAG) $(PSF)/portsf.c $(HS_FLAG) $(INCLUDE)
	$(CC) $(OBJFLAG) $(PSF)/ieee80.c 
	$(CC) $(OBJFLAG) $(BRK)/breakpoints.c $(HS_FLAG) "$(BRK)/include"
	$(CC) $(OBJFLAG) $(SRC3)/wave.c $(HS_FLAG) $(INCLUDE3)
	$(CC) $(OBJFLAG) Exercises$(EXERCIS).c $(HS_FLAG) $(INCLUDE) $(HS_FLAG) "$(BRK)/include" $(HS_FLAG) $(INCLUDE3)
	$(CC) $(EXEFLAG) ex Exercises$(EXERCIS).o ieee80.o portsf.o breakpoints.o wave.o $(MTHFLAG)

run:


clean:
	rm ./*.o
	clear

cleanAll:
	rm ./*.o
	rm ex
	clear
