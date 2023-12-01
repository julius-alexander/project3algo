#ifndef _HELPER_H_
#define _HELPER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <deque>

using namespace std;

enum DIRCT { E, SE, S, SW, W, NW, N, NE, NS };
enum COLOR { R, B, O };

struct node {
    COLOR color;
    DIRCT direction;
    int row_num;
    int col_num;
};


class ApolloDianaGraph {
    private:
        int rows;
        int cols;
        vector<vector<node>> board;
        unordered_map<node*, vector<pair<node*, int>>> adjacencies;

        // constructor helper functions, should not be called by user
        void parseBoard(string input_file);
        void assignDirection(node* n, string direction);
        void buildNeighbors(node* start);
        void scanBoard(node* start, int dx, int dy);
        
        vector<string> DFS();   // slightly faster than BFS for "apollodiana.txt"
        vector<string> BFS();   // incorrect output format

        // general helper functions for printing/ debugging
        // also should not be called by user
        void printBoard();
        void printAdjacencies();
        void printNode(node* n);

    public:
        // constructor
        ApolloDianaGraph(string input_file);
        
        void solveWrite(string output_file_name, string traversalMethod);

};

#endif
