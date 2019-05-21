#pragma once
#include "stdafx.h"
#include "Algorithm.h"

class Dfs : public Algorithm
{
public:
    Dfs(Board& board, std::forward_list<Node>& nodeGraph)
        : Algorithm(board, nodeGraph) {}
    ~Dfs() {};

    unsigned int run();

private:
    unsigned int recurse(Node& n);
};

