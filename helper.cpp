#include "helper.h"


ApolloDianaGraph::ApolloDianaGraph(ifstream& input_file) {
    
    parseBoard(input_file);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            buildNeighbors(&(board[i][j]));
        }
    }

}


void ApolloDianaGraph::parseBoard(ifstream& input_file) {
    // creates 2D matrix representing board
    // each element in matrix is a node*
    // each node* has a color and a direction
    // DOES NOT represent graph yet
    if (!input_file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }

    input_file >> rows >> cols;
    board.resize(rows, vector<node>(cols));

    node* temp;
    string color, line, direction;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            temp->row_num = i;
            temp->col_num = j;
            input_file >> line;
            color = line.substr(0, 1);
            
            if (color == "R" || color == "B") {
                direction = line.substr(2);
                assignDirection(temp, direction);
                temp->color = color=="R" ? R : B;
            } else if (color == "O") {
                temp->color = O;
                temp->direction = NS;     // dummy direction
            }
            
            board[i][j].color = temp->color;
            board[i][j].direction = temp->direction;
            board[i][j].row_num = temp->row_num;
            board[i][j].col_num = temp->col_num;
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


void ApolloDianaGraph::buildNeighbors(node* start) {

    switch (start->direction) {
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


void ApolloDianaGraph::scanBoard(node* start, int dx, int dy) {

    int next_row_num;
    int next_col_num;
    int count = 0;
    node* temp = start;
    vector<pair<node*, int>> edges;
    // follow arrow until boundary

    while ( (temp->row_num >= 0 && temp->row_num < rows) &&
            (temp->col_num >= 0 && temp->col_num < cols)) {

        next_row_num = temp->row_num + dx;
        next_col_num = temp->col_num + dy;
        if (next_row_num < 0 || next_row_num >= rows || next_col_num < 0 || next_col_num >= cols) {
            break;
        }
        temp = &(board[next_row_num][next_col_num]);

        count++;
        if (temp->color != start->color) {
            // add edge and weight between start and temp
            edges.push_back(make_pair(temp, count));
        }
    }
    adjacencies[start] = edges;

}


void ApolloDianaGraph::solveWrite(string output_file_name) {
    vector<string> result = DFS();
    ofstream output_file;
    output_file.open(output_file_name);
    if (result.empty()) {
        cout << "No path found" << endl;
    } else {
        for (int i = 0; i < result.size()-1; i++) {
            output_file << result[i];
        }
    }
    output_file.close();
}


vector<string> ApolloDianaGraph::DFS() {
    vector<string> dirctToString = {"E", "SE", "S", "SW", "W", "NW", "N", "NE", ""};
    vector<node*> stack;
    vector<int> weights;
    vector<string> finalAnswer;
    unordered_map<node*, bool> visited;

    stack.push_back(&(board[0][0]));
    visited[&(board[0][0])] = true;

    while (!stack.empty()) {
        node* curr = stack.back();

        if (curr->color == O) {
            string temp;
            for (int i = 0; i < stack.size(); i++) {
                temp = to_string(weights[i]) + dirctToString[stack[i]->direction] + " ";
                finalAnswer.push_back(temp);
            }
            return finalAnswer;
        }

        bool found_unvisited_neighbor = false;

        for (int i = 0; i < adjacencies[curr].size(); i++) {
            if (!visited[adjacencies[curr][i].first]) {
                stack.push_back(adjacencies[curr][i].first);
                weights.push_back(adjacencies[curr][i].second);
                visited[adjacencies[curr][i].first] = true;
                found_unvisited_neighbor = true;
                break;
            }
        }

        if (!found_unvisited_neighbor) {
            stack.pop_back();
            weights.pop_back();
        }

    }

    // If no path is found, return an empty vector
    return vector<string>();
}


void ApolloDianaGraph::printBoard() {
    // prints color and direction of each node* in board, according to enums
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            cout << "(" << board[i][j].row_num << ", " << board[i][j].col_num << ") " << board[i][j].color << " " << board[i][j].direction << "\t";
        }
        cout << "\n";
    }
}


void ApolloDianaGraph::printNode(node* n) {
    cout << "(" << n->row_num << ", " << n->col_num << ") " << n->color << " " << n->direction << " ";
}


void ApolloDianaGraph::printAdjacencies() {
    for (auto it = adjacencies.begin(); it != adjacencies.end(); it++) {
        cout << "start: ";
        printNode(it->first);
        cout << "\t[";
        for (int i = 0; i < it->second.size(); i++) {
            cout << "end: ";
            printNode(it->second[i].first);
            cout << " weight: " << it->second[i].second << "; ";
        }
        cout << "]" << endl;
        cout << endl << endl;
    }

}
