CFLAGS = -O3 -std=c++11 -Wall

all: main

main: main.cpp
	g++ $(CFLAGS) main.cpp -o main -lm

clean:
	rm -f *.o main test report

run: main
	./main

test: main ../tests/generate_graphs.cpp
	g++ $(CFLAGS) ../tests/generate_graphs.cpp -o test -lm

report: main ../tests/run_tests.cpp
	g++ $(CFLAGS) ../tests/run_tests.cpp -o report -lm
