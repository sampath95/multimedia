.PHONY: all

all: clean
	g++ -std=c++1y -o ed.o -c ed.cpp -Wall -O `pkg-config --cflags --libs opencv`
	g++ -o ed ed.o `pkg-config --cflags --libs opencv`

clean:
	rm -f *.o ed 

