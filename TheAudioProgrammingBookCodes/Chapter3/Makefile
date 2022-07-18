# Author: LucasPacheco

################################
EXE = helloRing#
################################

# Folders Flags
SRC1     = ../Resources/tinyaudiolib
INCLUDE1 = ../Resources/tinyaudiolib/include
SRC2     = ../Resources/portsf
INCLUDE2 = ../Resources/portsf/include

# Command Flags
CC      = gcc
OBJFLAG = -c
EXEFLAG = -o
HS_FLAG = -I
MTHFLAG = -lm

all:
	$(CC) $(OBJFLAG) $(SRC1)/tinyAudioLib.c $(HS_FLAG) $(INCLUDE1) $(HS_FLAG) C:\msys64\mingw64\include
	ar rc libtiny.a tinyAudioLib.o
	ranlib libtiny.a
	$(CC) $(OBJFLAG) $(SRC2)/portsf.c $(HS_FLAG) $(INCLUDE2)
	$(CC) $(OBJFLAG) $(SRC2)/ieee80.c $(HS_FLAG) $(INCLUDE2)
	ar rc libportsf.a portsf.o ieee80.o
	ranlib libportsf.a
	$(CC) $(EXEFLAG) $(EXE) $(EXE).c crack.c $(HS_FLAG) $(INCLUDE1) $(HS_FLAG) $(INCLUDE2) $(MTHFLAG) -L"../Chapter3/" -ltiny -lportaudio -lportsf
 

run:


clean:
	rm ./*.o
	clear

cleanAll:
	rm ./*.o
	rm ex
	clear
