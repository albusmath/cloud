CPP=g++

all:
	$(CPP) -Wall `gsl-config --cflags` -c test.cpp -g
	$(CPP) test.o `gsl-config --libs` -lglut
