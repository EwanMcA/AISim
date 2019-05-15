#include "stdafx.h"
#include "Board.h"
#include "Dfs.h"
#include "Bfs.h"

using std::cout;
using std::cin;
using std::endl;

int main(int argc, char* argv[]) 
{
    // Load the board
    Board origBoard;
    cout << "Map:" << endl;
    origBoard.load(argv[1]);
    cout << endl;

    // Run the game
    while(true) {
        std::forward_list<Node> nodeGraph;
        char choice;

        cout << "Enter:" << endl
             << "[1] for Breadth First Search" << endl
             << "[2] for Depth First Search" << endl
             << "[any other key] to quit" << endl;
        cin >> choice;
        
        Algorithm* alg;
        switch (choice) {
            case '1':
                alg = new Bfs(origBoard, nodeGraph);
                break;
            case '2':
                alg = new Dfs(origBoard, nodeGraph);
                break;
            default:
                return 1;
        }

        alg->run();
        alg->traceback();

        std::string line;
        cout << "Enter [Y/y] to run again or [any other key] to quit" << endl;
        cin >> line;
        if (line != "Y" && line != "y")
            return 0;
        origBoard.clear();
    }
}
