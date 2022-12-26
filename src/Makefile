CFLAGS = -O3 -std=c++11 -Wall

all: main

main: main.cpp
	g++ $(CFLAGS) main.cpp -o main -lm

clean:
	rm -f *.o main test output.txt

run: main
	./main

test: main ../tests/run_tests.cpp
	g++ $(CFLAGS) ../tests/run_tests.cpp -o test -lm
