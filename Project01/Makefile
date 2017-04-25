.PHONY: all

all: clean
	g++ -std=c++1y -o project0.o -c project0.cpp -Wall -O `pkg-config --cflags --libs opencv`
	g++ -o project0 project0.o `pkg-config --cflags --libs opencv`

clean:
	rm -f *.o project0 

