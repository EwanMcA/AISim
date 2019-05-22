#pragma once
#include "board.h"

class Algorithm
{
public:
    Algorithm(Board& board, std::forward_list<Node>& nodeGraph)
        : board(board), nodeGraph(nodeGraph)
    {}

    virtual ~Algorithm() {};

    /**********************************************************************************
    Runs the algorithm.
    
        Returns:
            unsigned int - The number of nodes searched.
    ***********************************************************************************/
    virtual unsigned int run() = 0;
    
    /**********************************************************************************
    Displays the game board with the calculated path highlighted.

        Returns:
            unsigned int - The number of steps in the path.
    ***********************************************************************************/
    virtual unsigned int traceback();

    std::forward_list<Node>& nodeGraph;
    Board& board;
};

