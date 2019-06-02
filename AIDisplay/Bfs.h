#pragma once
#include "pch.h"
#include "IterativeSearch.h"

class Bfs : public IterativeSearch
{
public:
    Bfs(Board& board, std::forward_list<Node>& nodeGraph)
        : IterativeSearch(board, nodeGraph), stablePrior(0) {}
    ~Bfs() {};
    
    // See IterativeSearch::get_priority(...)
    double get_priority(const Node& parent, int x, int y);
    
private:

    // Counter is used to sort nodes by insertion order (stable queue).
    int stablePrior;
};

