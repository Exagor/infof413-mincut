CC= g++
CFLAGS= -O3 -Wall -std=c++17

OBJECTS= src/main.o

.PHONY: clean

all: compile
	./main

compile: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o main

clean:
	rm -f src/*.o main