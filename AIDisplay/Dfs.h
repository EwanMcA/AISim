#pragma once
#include "pch.h"
#include "Algorithm.h"

class Dfs : public Algorithm
{
public:
    Dfs(Board& board, std::forward_list<Node>& nodeGraph)
        : Algorithm(board, nodeGraph) {}
    ~Dfs() {};

    /**********************************************************************************
    Runs the Depth First Search.

        Returns:
            unsigned int - The number of nodes searched.
    ***********************************************************************************/
    unsigned int run();

private:

    /**********************************************************************************
    Recursive step which is called for each node visited in the DFS.

        Returns:
            unsigned int - The number of nodes searched so far.
    ***********************************************************************************/
    unsigned int recurse(Node& n);
};

