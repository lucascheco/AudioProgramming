SRC2     = ../Resources/portsf
INCLUDE2 = ../Resources/portsf/include

waveform: rd.o out.o main.o portsf.a
	cc -o waveform rd.o out.o main.o portsf.a -lm

rd.o: rd.c waveform.h
	cc -c -g rd.c

out.o: out.c waveform.h $(INCLUDE2)/portsf.h
	cc -c -g out.c -I $(INCLUDE2)

main.o: main.c waveform.h $(INCLUDE2)/portsf.h
	cc -c -g main.c  -I $(INCLUDE2)

portsf.a: $(SRC2)/portsf.c $(SRC2)/ieee80.c $(INCLUDE2)/portsf.h $(INCLUDE2)/ieee80.h 
	cc -c $(SRC2)/portsf.c -I $(INCLUDE2)
	cc -c $(SRC2)/ieee80.c -I $(INCLUDE2)
	ar rv portsf.a portsf.o ieee80.o
	rm portsf.o ieee80.o