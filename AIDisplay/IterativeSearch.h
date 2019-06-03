#ifndef ITERATIVE_SEARCH_H
#define ITERATIVE_SEARCH_H

#include "Algorithm.h"

class NodePriority
{
public:
    bool operator() (Node& left, Node& right)
    {
        return left.priority > right.priority;
    }
};

class IterativeSearch : public Algorithm
{
public:
    IterativeSearch(Board& board, std::forward_list<Node>& nodeGraph)
        : Algorithm(board, nodeGraph) {}
    virtual ~IterativeSearch() {};
    
    /**********************************************************************************
    Returns the priority of a position on the board.
        
        const Node& - Parent node which defines the path to this position.
        const int   - X position being assessed.
        const int   - Y position being assessed.

        Returns:
            double - Numerical representation of priority (higher value is given lower
                     precedence in the queue).
    ***********************************************************************************/
    virtual double get_priority(const Node& parent, const int x, const int y);

    /**********************************************************************************
     Pushes the children of the given node to the priority queue.

        const Node& - Node whose children are to be added.
    ***********************************************************************************/
    void add_children(const Node& n);

    /**********************************************************************************
    Runs the search

        Returns:
            unsigned int - The number of nodes searched.
    ***********************************************************************************/
    unsigned int run();

private:

    // Priority queue which controls the order of node traversal
    std::priority_queue<Node, std::deque<Node>, NodePriority> pq;
    
};

#endif // ITERATIVE_SEARCH_H