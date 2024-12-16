CC= g++
CFLAGS= -O3 -Wall

OBJECTS= src/utilities.o src/Graph.o src/main.o 

.PHONY: clean

all: compile
	./main

compile: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o main

clean:
	rm -f src/*.o main