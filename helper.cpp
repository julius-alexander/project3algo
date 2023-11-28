#include "helper.h"


ApolloDianaGraph::ApolloDianaGraph(ifstream& input_file) {
    parseBoard(input_file);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "hello";
            buildNeighbors((board[i][j]));
        }
    }

    printAdjacencies();
    if (adjacencies.size() == 0) {
        cout << "No solution" << endl;
    }
}


void ApolloDianaGraph::parseBoard(ifstream& input_file) {
    // creates 2D matrix representing board
    // each element in matrix is a node
    // each node has a color and a direction
    // DOES NOT represent graph yet
    if (!input_file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }

    input_file >> rows >> cols;
    board.resize(rows, vector<node>(cols));
    
    node temp;
    string color, line, direction;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            temp.row_num = i;
            temp.col_num = j;
            input_file >> line;
            color = line.substr(0, 1);
            if (color == "O") {
                temp.color = O;
                temp.direction = NS;     // dummy direction
                board[i][j] = temp;
            } else if (color == "R" || color == "B") {
                direction = line.substr(2);
                assignDirection(&temp, direction);
                temp.color = color=="R" ? R : B;
                board[i][j] = temp;
            }
        }
    }
    input_file.close();
}


void ApolloDianaGraph::assignDirection(node* n, string direction) {
    if (direction == "N") {
        n->direction = N;
    } else if (direction == "E") {
        n->direction = E;
    } else if (direction == "S") {
        n->direction = S;
    } else if (direction == "W") {
        n->direction = W;
    } else if (direction == "NE") {
        n->direction = NE;
    } else if (direction == "SE") {
        n->direction = SE;
    } else if (direction == "SW") {
        n->direction = SW;
    } else if (direction == "NW") {
        n->direction = NW;
    }
}


void ApolloDianaGraph::buildNeighbors(node start) {

    switch (start.direction) {
        case (N):
            scanBoard(start, -1, 0);
            break;
        case (S):
            scanBoard(start, 1, 0);
            break;
        case (E):
            scanBoard(start, 0, 1);
            break;
        case (W):
            scanBoard(start, 0, -1);
            break;
        case (NE):
            scanBoard(start, -1, 1);
            break;
        case (NW):
            scanBoard(start, -1, -1);
            break;
        case (SE):
            scanBoard(start, 1, 1);
            break;
        case (SW):
            scanBoard(start, 1, -1);
            break;
        
        default:
            break;
    }

}


void ApolloDianaGraph::printBoard() {
    // prints color and direction of each node in board, according to enums
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            cout << board[i][j].color << " " << board[i][j].direction << "\t";
        }
        cout << "\n";
    }
}


void ApolloDianaGraph::scanBoard(node start, int dx, int dy) {
    
    node temp = start;
    int count = 0;
    vector<pair<node, int>> edges;
    // follow arrow until boundary
    while ( (temp.row_num >= 0 && temp.row_num < rows ) &&
            (temp.col_num >= 0 && temp.col_num < cols)) {
        temp = board[temp.row_num + dx][temp.col_num + dy];
        count++;
        if (temp.color != start.color) {
            // add edge and weight between start and temp
            edges.push_back(make_pair(temp, count));
        }
    }
    adjacencies[&start] = edges;
}


void ApolloDianaGraph::printAdjacencies() {

}


void ApolloDianaGraph::solveWrite() {

}