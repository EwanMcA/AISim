#ifndef ASTAR_H
#define ASTAR_H

#include "pch.h"
#include "IterativeSearch.h"

class AStar : public IterativeSearch
{
public:
    AStar(Board& board, std::forward_list<Node>& nodeGraph, int hScale)
        : IterativeSearch(board, nodeGraph), hScale(hScale) {}
    ~AStar() {};

    // See IterativeSearch::get_priority(...)
    double get_priority(const Node& parent, int x, int y);

    private:
        // Scale up the A* heuristic, causing an aggressive preference for 
        // nodes closer to the end-point.
        int hScale;
};

#endif // ASTAR_H