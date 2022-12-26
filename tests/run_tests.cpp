#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>

int main(int argc, char *argv[]) {
    // Check if the number of test cases is provided
    if (argc < 2) {
        std::cerr << "Usage: ./test <number of tests>\n";
        return EXIT_FAILURE;
    }

    // Parses the number of test cases
    int num_test_cases = std::stoi(argv[1]);
    if (num_test_cases < 1) {
        std::cerr << "Error: Please insert a valid number of tests\n";
        return EXIT_FAILURE;
    }

    // Removed potentially old output file and opens a new one
    std::remove("output.txt");
    std::ofstream out("output.txt");

    // Creates a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);

    // Generates the test cases
    for (int i = 1; i <= num_test_cases; i++) {
        // Creates the input file
        std::ofstream in("input.txt");

        // Writes the number of vertices and edges
        int num_vertices = i;
        int num_edges = num_vertices * (num_vertices - 1) / 2;
        in << num_vertices << "\n";
        in << num_edges << "\n";

        // Writes the edges information
        for (int j = 1; j <= num_vertices; j++) {
            for (int k = j + 1; k <= num_vertices; k++) {
                int weight = dist(gen);
                in << j << " " << k << " " << weight << "\n";
            }
        }

        // Closes the input file
        in.close();

        // Calls the main program with the input file and redirects the output
        // to the output file
        std::system("../src/main < input.txt >> output.txt");

        // Removes the input file for the next iteration to use a different one
        std::remove("input.txt");
    }

    return 0;
}
