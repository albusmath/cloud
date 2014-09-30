SRCDIR=.
CPP=g++
CFLAGS=-g -Wall `gsl-config --cflags` -I$(SRCDIR)/include
LDLIBS=`gsl-config --libs` -lglut
TARGETS=test

HEADERS=include/Matrix.h


all:$(TARGETS)

test:$(SRCDIR)/test.cpp $(HEADERS) Matrix.o
	$(CPP) -c test.cpp $(CFLAGS)
	$(CPP) test.o Matrix.o -o $@ $(LDLIBS)

Matrix.o: include/Matrix.cpp include/Matrix.h
	$(CPP) -c include/Matrix.cpp $(CFLAGS)
	
clean:
	rm $(TARGETS) *.o

