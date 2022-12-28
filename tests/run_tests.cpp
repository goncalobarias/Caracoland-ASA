#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>

#define MAX_TRADES 100
#define INPUT_FILE_NAME_LEN 15
#define COMMAND_LEN 256

// Number of tests to run
int _numTests;

// Files to write the output
std::ofstream edges("edges.csv");
std::ofstream report("report.csv");

void printUsage(char *progName) {
    std::cout << "Usage: " << progName << " #T seed\n";
    std::cout << "\t#T: number of tests\n";
    std::cout << "\tseed: random seed number (optional)\n";
    exit(1);
}

void parseArgs(int argc, char **argv) {
    int seed = 0;

    if (argc < 2 || argc > 3) {
        std::cout << "ERROR: invalid number of arguments\n";
        printUsage(argv[0]);
    }

    sscanf(argv[1], "%d", &_numTests);
    if (_numTests <= 9) {
        std::cout << "ERROR: number of tests must be >= 10\n";
        printUsage(argv[0]);
    }

    if (argc == 3) { // Init rand seed
        sscanf(argv[2], "%d", &seed);
        srand(seed);
    } else { // pseudo-rand seed
        srand((unsigned int)time(NULL));
    }
}

inline int randomValue(int max) {
    return rand() % max; // [0, max - 1]
}

void writeReport(int numV, int numE) {
    // Open input file
    char inputFileName[INPUT_FILE_NAME_LEN];
    memset(inputFileName, 0, INPUT_FILE_NAME_LEN);
    sprintf(inputFileName, "%d.txt", numE);
    std::ofstream input(inputFileName);

    // Print header
    input << numV << "\n" << numE << "\n";

    // Print the edges information
    int edgeCounter = 0;
    for (int i = 1; i <= numV && edgeCounter < numE; i++) {
        for (int j = i + 1; j <= numV && edgeCounter < numE; j++) {
            input << i << " " << j << " " << randomValue(MAX_TRADES) << "\n";
            edgeCounter++;
        }
    }

    // Close input file
    input.close();

    // Execute the hyperfine command
    char command[COMMAND_LEN];
    memset(command, 0, COMMAND_LEN);
    sprintf(command,
            "hyperfine -m 100 -u second --export-csv temp.csv "
            "\"./main < ./%s\"",
            inputFileName);
    std::system(command);

    // Copy the command output into the report.csv file
    std::ifstream temp("temp.csv");
    std::string line;
    std::getline(temp, line);
    std::getline(temp, line);
    report << line << "\n";
    temp.close();

    // Remove all temporary files
    remove("temp.csv");
    remove(inputFileName);
}

void writeEdges(int numV, int numE) { edges << numE << "," << numV << "\n"; }

void runTests() {
    int i = 10, numIncrements = 0;
    while (i <= _numTests) {
        if (i == pow(10, numIncrements + 2)) {
            numIncrements++;
        }

        // Calculate number of edges and vertices
        int numE = i;
        int numV = ceil((1 + sqrt(8 * numE + 1)) / 2);

        // Writes to the edges.csv and report.csv files
        writeEdges(numV, numE);
        writeReport(numV, numE);

        // Increments the number of the test correctly (1, 10 when it reaches
        // 1000, then 100 when it reaches 10000, and so on)
        i += pow(10, numIncrements);
    }
}

int main(int argc, char *argv[]) {
    // Parse arguments
    parseArgs(argc, argv);

    // Write initial csv input
    edges << "e,v\n";
    report << "command,mean,stddev,median,user,system,min,max\n";

    // Run tests
    runTests();

    // Close all the output files
    report.close();
    edges.close();

    return 0;
}
