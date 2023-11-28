#ifndef _HELPER_H_
#define _HELPER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

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
        vector<vector<node> > board;
        unordered_map<node*, vector<pair<node, int> > > adjacencies;

    public:
        // constructor
        ApolloDianaGraph(ifstream& input_file);

        // helper functions
        void parseBoard(ifstream& input_file);
        void assignDirection(node* n, string direction);
        void buildNeighbors(node start);
        void solveWrite();

        void scanBoard(node start, int dx, int dy);
    
        void printBoard();
        void printAdjacencies();

};

#endif
