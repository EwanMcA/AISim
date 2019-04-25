#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <thread>

#define WALL "H"
#define START "s"
#define END "e"
#define IS_WALL(x) ((x) == WALL)
#define IS_START(x) ((x) == START)
#define IS_END(x) ((x) == END)

using std::cout;
using std::cin;
using std::endl;

typedef std::pair<int, int> Node;
typedef std::vector<std::vector<std::string>> Board;

// Print the board
void display(Board board) {
    std::stringstream ss;
    for (auto & v : board) {
        ss << "\t";
        for (auto & s : v) {
            ss << s << " ";
        }
        ss << endl;
    }
    ss << endl << endl;
    cout << ss.str() ;
}

// Find the starting point (start at 0,0 if not specified).
Node find_start(Board board) {
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if (IS_START(board[i][j])) 
                return { i, j };
        }
    }
    return { 0, 0 };
}

// Add the children of the front node to the end of the queue
void add_children(int size, std::queue<Node>& q) {
    Node n(q.front());

    if (n.first > 0) {
        q.push({n.first-1, n.second});
    } 
    if (n.second > 0) {
        q.push({n.first, n.second-1});
    } 
    if (n.first < size - 1) {
        q.push({n.first+1, n.second});
    } 
    if (n.second < size - 1) {
        q.push({n.first, n.second+1});
    } 
}

// Breadth first search (iterative)
int bfs(Board board) {
    std::chrono::milliseconds t(150);

    int steps(0);
    std::queue<Node> q;
    q.push(find_start(board));
    q.push({-1, -1});
    add_children(board.size(), q);

    while(!q.empty()) {
        if (q.front().first == -1) {
            ++steps;
            q.push({ -1, -1 });
        } else if (board[q.front().first][q.front().second] == "*") {
            q.pop();
            continue;
        } else if (IS_END(board[q.front().first][q.front().second])) {
            return steps;
        } else if (!IS_WALL(board[q.front().first][q.front().second]) && 
                   !IS_START(board[q.front().first][q.front().second])) {
            add_children(board.size(), q);
            board[q.front().first][q.front().second] = "*";
            display(board);
            std::this_thread::sleep_for(t);
        }
        q.pop();
    }

    return 0;
}

std::vector<std::string> split_string(std::string input_string) {
    std::vector<std::string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != std::string::npos) {
        if (input_string.substr(i, pos - i) != "|") {
            splits.push_back(input_string.substr(i, pos - i));
        }

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    if (input_string.substr(i, std::min(pos, input_string.length()) - i + 1) != "|") {
        splits.push_back(input_string.substr(i, std::min(pos, input_string.length()) - i + 1));
    }

    return splits;
}

int main(int argc, char* argv[]) 
{
    // Load the board
    Board origBoard;
    std::string line;
    std::ifstream fs;
    fs.open(argv[1]);
    if (fs.is_open()) {
        while (std::getline(fs, line)) {
            cout << line << endl;
            origBoard.push_back(split_string(line));
        }
        fs.close();
    } else {
        cout << "failed to open file: " << argv[1] << endl;
    }

    // Run the game
    Board board(origBoard);
    do {
        cout << "Minimum steps: " << bfs(board) << endl;
        cout << "[q] to quit or [r] to run again" << endl;
        cin >> line;
    } while (line == "r");
}
