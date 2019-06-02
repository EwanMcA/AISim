#include "pch.h"
#include "Bfs.h"

// In this case the priority is determined with a simple counter, to replicate a 
// stable queue
double Bfs::get_priority(const Node& parent, int x, int y)
{
    return stablePrior++;
}
