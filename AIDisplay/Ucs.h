#pragma once
#include "Algorithm.h"

class NodePriority
{
public:
    bool operator() (Node& left, Node& right)
    {
        return left.priority > right.priority;
    }
};

class Ucs : public Algorithm
{
public:
    Ucs(Board& board, std::forward_list<Node>& nodeGraph)
        : Algorithm(board, nodeGraph) {}
    virtual ~Ucs() {};
    
    void add_children(Board& board, 
                      Node& n, 
                      std::priority_queue<Node, std::deque<Node>, NodePriority>& q);
    unsigned int run();

    virtual double get_priority(Board& board, Node& parent, int x, int y);
};

