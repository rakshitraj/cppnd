#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;
using std::abs;

// Declare an enumerated object that contains possible states in the gridworld
enum class State {kEmpty, kObstacle};


// Alll funtion prototypes

/**
 * @brief funtion to parse lines from input gridworld
 * 
 * @param line Row from Gridworld matrix
 * @return std::vector<State> 
 */
std::vector<State> ParseLine(std::string line) {
    std::istringstream sline(line); // input stream
    int n; // target variable to store parsed integers
    char c; // target variable to parse char delimmiter

    vector<State> row;
    while(sline >> n >> c && c == ',') {
        if (n == 0) row.push_back(State::kEmpty);
        else row.push_back(State::kObstacle);
    }
    return row;
}

/**
 * @brief Function to construct gridworld from file
 * 
 * @param path 
 * @return std::vector<std::vector<State>> 
 */
std::vector<std::vector<State>> ReadBoardFile(std::string path) {
    std::ifstream myfile (path);
    std::vector<std::vector<State>> board{};
    if (myfile) {
        std::string line;
        while (getline(myfile, line)) {
            std::vector<State> row = ParseLine(line);
            board.push_back(row);
        }
    }
    return board;
}


// TODO: Write the Search function stub here.

std::vector<std::vector<State>> Search (std::vector<std::vector<State>> grid, int init[2], int goal[2]) {
    cout<<"No path found" << '\n';
    return std::vector<std::vector<State>> {};
}


std::string CellString(State cell){
    switch (cell)
    {
    case State::kObstacle: return "⛰️   ";
        break;
    default: return "0   ";
    }
}


void PrintBoard(const std::vector<std::vector<State>> board) {
    for (int i=0; i<board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            cout << CellString(board[i][j]); 
        }
        cout << '\n';
    }
}


/**
 * @brief Heuristic Funtion for A* Search
 * 
 * @param x1 x-coordinate of point P1
 * @param y1 y-coordinate of point P1
 * @param x2 x-coordinate of point P2
 * @param y2 y-coordinate of point P2
 * @return int  Manhattan distance from point P2 to P1
 */
int Heuristic(int x1, int y1, int x2, int y2) {
    return std::abs(x2-x1) + std::abs(y2-y1);
}

int main(int argc, char *argv[]) {
    // TODO: Declare "init" and "goal" arrays with values {0, 0} and {4, 5} respectively.
    int init[2] {0, 0};
    int goal[2] {4, 5};
    
    std::string path = "";
    if (argv[1]) path = argv[1];
    else path = "1.board";
    std::vector<std::vector<State>> board = ReadBoardFile(path);
    PrintBoard(board);
    // TODO: Call Search with "board", "init", and "goal". Store the results in the variable "solution".
    auto solution = Search(board, init, goal);
    // TODO: Change the following line to pass "solution" to PrintBoard.
    PrintBoard(solution);
    return 0;
}
