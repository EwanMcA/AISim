#include "pch.h"
#include "AStar.h"
#include "Bfs.h"
#include "Board.h"
#include "Dfs.h"
#include "IterativeSearch.h"

using std::cout;
using std::cin;
using std::endl;

bool run(Board& board)
{
    std::forward_list<Node> nodeGraph;
    char choice;

    cout << "Enter:" << endl
        << "[1] for Breadth First Search" << endl
        << "[2] for Depth First Search" << endl
        << "[3] for Uniform Cost Search" << endl
        << "[4] for A* Search - Admissible (shortest path guaranteed)" << endl
        << "[5] for A* Search - Aggressive" << endl
        << "[any other key] to quit" << endl << endl;
    cin >> choice;

    std::unique_ptr<Algorithm> alg;

    switch (choice) {
    case '1':
        alg = std::make_unique<Bfs>(board, nodeGraph);
        break;
    case '2':
        alg = std::make_unique<Dfs>(board, nodeGraph);
        break;
    case '3':
        alg = std::make_unique<IterativeSearch>(board, nodeGraph);
        break;
    case '4':
        alg = std::make_unique<AStar>(board, nodeGraph, 1);
        break;
    case '5':
        alg = std::make_unique<AStar>(board, nodeGraph, 2);
        break;
    default:
        return false;
    }

    while (true) {
        unsigned int searched = alg->run();
        std::cout << "Path length: " << alg->traceback() << endl;
        cout << "Nodes searched: " << searched << endl << endl;

        std::string line;
        cout << "Enter:" << endl
            << "[1] to run again" << endl
            << "[2] to choose another algorithm" << endl
            << "[any other key] to quit" << endl << endl;
        cin >> line;

        board.clear();
        nodeGraph.clear();

        if (line == "2")
            return true;
        else if (line != "1")
            return false;
    }
}

int main(int argc, char* argv[]) 
{
    // Load the board
    Board origBoard;

    std::string line;
    do {
        cout << "Enter a map file (or hit [enter] for example map):" << endl;
        getline(cin, line);
        if (line.empty())
            line = "example.in";
    } while(!origBoard.load(line.c_str()));
    
    cout << "Map:" << endl << endl;;

    // Run the game
    while (run(origBoard));
}
