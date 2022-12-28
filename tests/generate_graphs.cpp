#include <fstream>
#include <iostream>

#define MAX_TRADES 100

// Number of vertices and edges
int _numV;
int _numE;

void printUsage(char *progname) {
    std::cout << "Usage: " << progname << " #V #E seed\n";
    std::cout << "\t#V: number of vertices\n";
    std::cout << "\t#E: number of edges\n";
    std::cout << "\tseed: random seed number (optional)\n";
    exit(1);
}

void parseArgs(int argc, char **argv) {
    int seed = 0;

    if (argc < 3 || argc > 4) {
        std::cout << "ERROR: invalid # arguments\n";
        printUsage(argv[0]);
    }

    sscanf(argv[1], "%d", &_numV);
    if (_numV <= 0) {
        std::cout << "ERROR: #V vertices must be >= 1\n";
        printUsage(argv[0]);
    }

    sscanf(argv[2], "%d", &_numE);
    if (_numE <= 0) {
        std::cout << "ERROR: #E edges must be >= 1\n";
        printUsage(argv[0]);
    }
    if (_numE > _numV * (_numV - 1) / 2) {
        std::cout << "ERROR: #E edges is too large\n";
        printUsage(argv[0]);
    }

    if (argc == 4) { // Init rand seed
        sscanf(argv[3], "%d", &seed);
        srand(seed);
    } else { // pseudo-rand seed
        srand((unsigned int)time(NULL));
    }
}

inline int randomValue(int max) {
    return rand() % max; // [0, max - 1]
}

int main(int argc, char *argv[]) {
    // parse arguments
    parseArgs(argc, argv);

    // Open input file
    std::ofstream input("input.txt");

    // Print header
    input << _numV << "\n" << _numE << "\n";

    // Print the edges information
    int edgeCounter = 0;
    for (int j = 1; j <= _numV && edgeCounter < _numE; j++) {
        for (int k = j + 1; k <= _numV && edgeCounter < _numE; k++) {
            input << j << " " << k << " " << randomValue(MAX_TRADES) << "\n";
            edgeCounter++;
        }
    }

    // Close input file
    input.close();

    return 0;
}
