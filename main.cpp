#include "helper.h"

int main() {

    // assuming "input.txt" exists and is formatted correctly
    ifstream input_file;
    input_file.open("input.txt");
    
    // parse input file and create graph; constructor closes file
    ApolloDianaGraph graph(input_file);

    // save problem solution to output file specified below
    string output_file_name = "output.txt";
    graph.solveWrite(output_file_name);

    return 0;
}
