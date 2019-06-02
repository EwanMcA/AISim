#include "pch.h"
#include "AStar.h"

/* 
In this case the priority is equal to the cost to reach the given position + the chosen 
heuristic (diagonal distance to the end-point). The heuristic is multiplied by a scaling 
factor which can make the algorithm more aggressive (and violate admissibility).*/
double AStar::get_priority(const Node& parent, int x, int y)
{
    int dx = abs(board.end.first - x);
    int dy = abs(board.end.second - y);
    return parent.priority + 1.0 + (dx + dy - std::min(dx, dy)) * hScale;
}
