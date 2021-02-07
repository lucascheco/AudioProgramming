# Author: LucasPacheco
# My template for makefiles

################################
#Just modify the exercise number
EXERCIS = 225#
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
	$(CC) $(OBJFLAG) Exercises$(EXERCIS).c $(HS_FLAG) $(INCLUDE)
	$(CC) $(EXEFLAG) ex Exercises$(EXERCIS).o ieee80.o portsf.o $(MTHFLAG)

run:


clean:
	rm ./*.o
	clear

cleanAll:
	rm ./*.o
	rm ex
	clear
