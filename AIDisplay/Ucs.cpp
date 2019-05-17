#include "Ucs.h"

double Ucs::get_priority(Board& board, Node& parent, int x, int y) {
    return parent.priority + 1;
}

// Add the children of the front node to the pqueue
void Ucs::add_children(Board& board, Node& n, std::priority_queue<Node, std::deque<Node>, NodePriority>& q) 
{

    if (n.x > 0) {
        q.push({ n.x - 1, n.y, &n, get_priority(board, n, n.x - 1, n.y) });
    }
    if (n.y > 0) {
        q.push({ n.x, n.y - 1, &n, get_priority(board, n, n.x, n.y - 1) });
    }
    if (n.x < board.size() - 1) {
        q.push({ n.x + 1, n.y, &n, get_priority(board, n, n.x + 1, n.y) });
    }
    if (n.y < board.size() - 1) {
        q.push({ n.x, n.y + 1, &n, get_priority(board, n, n.x, n.y + 1) });
    }
}

// Breadth first search (iterative)
unsigned int Ucs::run()
{
    std::priority_queue <Node, std::deque<Node>, NodePriority> q;
    nodeGraph.emplace_front(board.findStart());
    q.push(nodeGraph.front());
    add_children(board, nodeGraph.front(), q);
    int searched(0);

    while (!q.empty()) {
        Node n(q.top());
        q.pop();

        if (board.isDiscovered(n.x, n.y)) {
            continue;
        }
        else if (board.isEnd(n.x, n.y)) {
            nodeGraph.emplace_front(n);
            return searched;
        }
        else if (!board.isWall(n.x, n.y) && !board.isStart(n.x, n.y)) {
            nodeGraph.emplace_front(n);
            add_children(board, nodeGraph.front(), q);
            board.discover(n.x, n.y);
            board.display();
            searched++;
        }
    }
}
