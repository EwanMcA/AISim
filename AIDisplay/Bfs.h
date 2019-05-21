#pragma once
#include "stdafx.h"
#include "Ucs.h"

class Bfs : public Ucs
{
public:
    Bfs(Board& board, std::forward_list<Node>& nodeGraph)
        : Ucs(board, nodeGraph), stablePrior(0) {}
    ~Bfs() {};

    double get_priority(Board& board, Node& parent, int x, int y) { return ++stablePrior; }
    
private:
    int stablePrior;
};

