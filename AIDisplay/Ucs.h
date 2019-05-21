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

    virtual void add_children(Board& board, Node& n);
    virtual double get_priority(Board& board, Node& parent, int x, int y);
    virtual unsigned int run();

private:
    std::priority_queue<Node, std::deque<Node>, NodePriority> pq;
};

