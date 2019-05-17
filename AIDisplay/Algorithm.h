#pragma once
#include "board.h"

class Algorithm
{
public:
    Algorithm(Board& board, std::forward_list<Node>& nodeGraph)
        : board(board), nodeGraph(nodeGraph)
    {}

    virtual ~Algorithm() {};

    virtual unsigned int run() = 0;
    virtual unsigned int traceback();

    std::forward_list<Node>& nodeGraph;
    Board& board;
};

