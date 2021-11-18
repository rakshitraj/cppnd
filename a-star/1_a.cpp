#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;
using std::abs;

// Declare an enumerated object that contains possible states in the gridworld
enum class State {kPath, kEmpty, kObstacle, kClosed};

// Directional deltas
const int delta[4][2] = {{-1,0}, {0,-1}, {1, 0}, {0, 1}};


// All funtion prototypes
std::vector<State> ParseLine(std::string); 
std::vector<std::vector<State>> ReadBoardFile (std::string);
std::string CellString (State);
void PrintBoard (const std::vector<std::vector<State>>);
int Heuristic (int, int, int, int);
void AddToOpen (int, int, int, int, std::vector<std::vector<int>>&, std::vector<std::vector<State>>&);
void CellSort (vector<vector<int>> *);
bool CheckValidCell (int, int, const vector<vector<State>> &); 
void ExpandNighbors (vector<int>&, vector<vector<int>>&, vector<vector<State>>&, int[2]);
std::vector<std::vector<State>> Search (std::vector<std::vector<State>>, int[2], int[2]);

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


/**
 * @brief Returns image objects for values in the gridworld
 * 
 * @param cell Cell of the gridworld
 * @return std::string 
 */
string CellString(State cell) {
  switch(cell) {
    case State::kObstacle: return "⛰️   ";
    case State::kPath: return "🚗   ";
    default: return "0   "; 
  }
}


/**
 * @brief Prints the Gridworld
 * 
 * @param board 
 */
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



/**
 * @brief Adds open node top open list and marks rid cells as closed
 * 
 * @param x 
 * @param y 
 * @param g g-value of cell
 * @param h heuristic value of cell 
 * @param openNodes Vector of open nodes
 * @param grid Gridworld matrix
 */
void AddToOpen(int x, int y, int g, int h, std::vector<std::vector<int>>& openNodes, std::vector<std::vector<State>>& grid) {
    
    // Create a vector node in the form (x,y,g,h) and push vector node to open list
    openNodes.push_back(std::vector<int> {x, y, g, h});
    // Set grid value for (x,y) as blocked
    grid[x][y] = State::kClosed;
}


/**
 * @brief Compares two cells and returns true if the first cell has greater sum of g-value and heuristic-value
 * 
 * @param node1 
 * @param node2 
 * @return true 
 * @return false 
 */
bool Compare (std::vector<int> node1, std::vector<int> node2) {
    if ((node1[2]+node1[3]) > (node2[2]+node2[3])) return true;
    return false;
}


/**
 * @brief sorts cells in DESC order of f-value 'f = g + h'. Closer to end, more the viability
 * 
 * @param v Open List vector
 */
void CellSort(vector<vector<int>> *v) {
    sort(v->begin(), v->end(), Compare);
}


/**
 * @brief Checks if a Cell is valid, i.e. navigable
 * 
 * @param x 
 * @param y 
 * @param grid 
 * @return true 
 * @return false 
 */
bool CheckValidCell(int x, int y, const vector<vector<State>> &grid) {
    if (x < grid.size() && y < grid[0].size() && grid[x][y] == State::kEmpty)
            return true;
    return false;
}


/**
 * @brief Expands A* Search into proximial cells or, neighboring cells
 * 
 * @param current 
 * @param goal 
 * @param openNodes 
 * @param grid 
 */
void ExpandNeighbors (vector<int>& current, int goal[2], vector<vector<int>>& openNodes, vector<vector<State>>& grid) {
    // Get current node's data
    int x = current[0];
    int y = current[1];
    int g = current[2];

    //Loop through current cells's potential neighbors
    for (int i=0; i<4; i++) {
        int x2 = x + delta[i][0];
        int y2 = y + delta[i][1];

        //check that th potemtial neighbour's coordinates are on the grod and not closed, i.e. cell is valid
        if (CheckValidCell(x2,y2, grid)) {
            // Increment g value and add neighbor to open list 
            int g2 = g+1;
            int h2 = Heuristic(x2, y2, goal[0], goal[1]);

            // Add nighbour node to open List
            AddToOpen(x2, y2, g2, h2, openNodes, grid);
        }
    }
}

/**
 * @brief Implements A* Search Algorithm
 * 
 * @param grid Gridworld matrix
 * @param init Coordinates of starting point 
 * @param goal Coordinates of end point
 * @return std::vector<std::vector<State>> 
 */
std::vector<std::vector<State>> Search (std::vector<std::vector<State>> grid, int init[2], int goal[2]) {
    
    // Create the vector of open nodes.
    vector<vector<int>> open {};
    // Initialize the starting node. 
    int x = init[0];
    int y = init[1];
    int g = 0;
    int h = Heuristic(x, y, goal[0],goal[1]);
    // Use AddToOpen to add the starting node to the open vector.
    AddToOpen(x, y, g, h, open, grid);
    // while open vector is non empty
    while(open.size() > 0) {
        // Sort open list using CellSort, and get the current node
        CellSort(&open);
        auto current = open.back();
        open.pop_back();
        // Get the x and y values from the current node
        x = current[0];
        y = current[1];
        grid[x][y] = State::kPath;
        // Check if agent has reached the goal. If so, return grid
        if (x == goal[0] && y== goal[1])
            return grid;
    }
    // We've run out of new nodes to explore and haven't found a path.
    cout<<"No path found" << '\n';
    return std::vector<std::vector<State>> {};
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
 