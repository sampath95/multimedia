.PHONY: all

all: clean
	g++ -std=c++1y -o project.o -c project.cpp -Wall -O `pkg-config --cflags --libs opencv`
	g++ -o project project.o `pkg-config --cflags --libs opencv`

clean:
	rm -f *.o project

