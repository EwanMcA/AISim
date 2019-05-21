#include "stdafx.h"
#include "Algorithm.h"

unsigned int Algorithm::traceback()
{
    unsigned int steps(1);
    Node& n(*nodeGraph.front().parent);
    board.clear();
    while (n.parent != nullptr) {
        board.discover(n.x, n.y);
        n = *n.parent;
        ++steps;
    }
    board.display();
    std::cout << std::endl;

    return steps;
}