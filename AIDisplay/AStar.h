#pragma once
#include "stdafx.h"
#include "Ucs.h"

class AStar : public Ucs
{
public:
    AStar(Board& board, std::forward_list<Node>& nodeGraph)
        : Ucs(board, nodeGraph) {}
    ~AStar() {};

    double get_priority(Board& board, Node& parent, int x, int y);
};

