CC=g++
CFLAGS=-O3 -funroll-loops -c -std=c++11
LDFLAGS=-O2 -lm
SOURCES := $(shell find . -name '*.cc')
OBJECTS=$(addsuffix .o, $(basename ${SOURCES}))
EXECUTABLE=main

all: $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o: *.h
	$(CC) $(CFLAGS) $< -o $@

clean: 
	-rm -f ${EXECUTABLE} ${OBJECTS} *.d
	-rm -f debug.txt

zip: clean
	tar -czf bot.tar.gz *

.PHONY: all clean

