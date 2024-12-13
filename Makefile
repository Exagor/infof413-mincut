CC=gcc
CFLAGS=-O3 -Wall
LDFLAGS = -lm

OBJECTS= src/utilities.o src/main.o src/quicksort.o src/selection.o

.PHONY: clean

all: selection
	./main

selection: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o main

clean:
	rm -f src/*.o main