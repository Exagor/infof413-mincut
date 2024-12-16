CC= g++
CFLAGS= -O3 -Wall -std=c++17

OBJECTS= src/utilities.o src/Graph.o src/main.o 

.PHONY: clean

all: compile
	./main

compile: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o main

clean:
	rm -f src/*.o main