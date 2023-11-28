#include "helper.h"

int main() {

    // assuming "input.txt" exists and is formatted correctly
    ifstream input_file;
    input_file.open("apollodiana.txt");
    // parse input file and create graph; constructor closes file
    ApolloDianaGraph graph(input_file);
    // graph.printBoard();

    // save problem solution to output file
    // graph.solveWrite();

    return 0;
}
