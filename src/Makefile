CFLAGS = -O3 -std=c++11 -Wall

all: main

main: main.cpp
	g++ $(CFLAGS) main.cpp -o main -lm

clean:
	rm -f *.o main

run: main
	./main
