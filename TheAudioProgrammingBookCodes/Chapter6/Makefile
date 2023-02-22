PROG = simplesynth
all:
	g++ -o ./bin/$(PROG) $(PROG).cpp oscil.cpp soundio.cpp ftables.cpp -lm -lsndfile -I.

run:
	./$(PROG)