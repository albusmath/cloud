SRCDIR=.
CPP=g++
CFLAGS=-g -Wall -I/usr/include/eigen3
LDLIBS=-lglut -lGL -lGLU
TARGETS=test

all:$(TARGETS)

test:$(SRCDIR)/test.cpp $(HEADERS)
	$(CPP) -c test.cpp $(CFLAGS)
	$(CPP) test.o -o $@ $(LDLIBS)

clean:
	rm $(TARGETS) *.o

