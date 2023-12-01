#include "helper.h"

int main() {

    // assuming "input.txt" exists and is formatted correctly
    // ifstream input_file;
    string input_file = "apollodiana.txt";

    // parse input file and create graph; constructor closes file
    ApolloDianaGraph graph(input_file);

    // save problem solution to output file specified below
    string output_file_name = "output.txt";
    
    // "BFS" technically works, but output is not in correct format...
    // * use DFS only * //
    graph.solveWrite(output_file_name, "DFS");

    return 0;
}
