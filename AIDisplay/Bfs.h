#pragma once
#include "stdafx.h"
#include "Algorithm.h"

class Bfs : public Algorithm
{
public:
    Bfs(Board& board, std::forward_list<Node>& nodeGraph)
        : Algorithm(board, nodeGraph) {}
    ~Bfs() {};

    void run();
};

