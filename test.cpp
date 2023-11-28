#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct node {
    string color;
    string direction;
    vector<node*> neighbors;
};

vector<node> board;

int main() {
    fstream input_file;
    input_file.open("apollodiana.txt");
    int rows, cols;
    input_file >> rows >> cols;
    cout << rows << " " << cols << endl;

    string line;
    string color;
    string direction;
    node temp;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            input_file >> line;
            color = line.substr(0, 1);
            temp.color = color;
            if (color == "O") {
                cout << "O" << " ";
                temp.direction = "";
                board.push_back(temp);
                break;
            }
            direction = line.substr(2);
            temp.direction = direction;
            board.push_back(temp);
            cout << color << " " << direction << "\t";
        }
        cout << "\n";
    }

    input_file.close();
    return 0;
}
