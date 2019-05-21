#pragma once
#include "stdafx.h"
#include "Ucs.h"

class AStar : public Ucs
{
public:
    AStar(Board& board, std::forward_list<Node>& nodeGraph, int hScale)
        : Ucs(board, nodeGraph), hScale(hScale) {}
    ~AStar() {};

    double get_priority(Board& board, Node& parent, int x, int y);

    private:
        // Scale up the A* heuristic, causing an aggressive preference for 
        // nodes closer to the end-point.
        int hScale;
};
