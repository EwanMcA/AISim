#include "Ucs.h"

double Ucs::get_priority(Board& board, Node& parent, int x, int y) {
    return parent.priority + 1;
}

// Add the children of the given node to the pqueue
void Ucs::add_children(Board& board, Node& n) 
{
    bool up(n.x > 0), left(n.y > 0), down(n.x < board.size() - 1), right(n.y < board.size() - 1);

    if (up) {
        pq.push({ n.x - 1, n.y, &n, get_priority(board, n, n.x - 1, n.y) });
        if (right)
            pq.push({ n.x - 1, n.y + 1, &n, get_priority(board, n, n.x - 1, n.y + 1) });
    }
    if (left) {
        pq.push({ n.x, n.y - 1, &n, get_priority(board, n, n.x, n.y - 1) });
        if (up)
            pq.push({ n.x - 1, n.y - 1, &n, get_priority(board, n, n.x - 1, n.y - 1) });
    }
    if (down) {
        pq.push({ n.x + 1, n.y, &n, get_priority(board, n, n.x + 1, n.y) });
        if (left)
            pq.push({ n.x + 1, n.y - 1, &n, get_priority(board, n, n.x + 1, n.y - 1) });
    }
    if (right) {
        pq.push({ n.x, n.y + 1, &n, get_priority(board, n, n.x, n.y + 1) });
        if (down)
            pq.push({ n.x + 1, n.y + 1, &n, get_priority(board, n, n.x + 1, n.y + 1) });
    }
}

// Breadth first search (iterative)
unsigned int Ucs::run()
{
    nodeGraph.emplace_front(board.findStart());
    pq.push(nodeGraph.front());
    add_children(board, nodeGraph.front());
    int searched(0);

    while (!pq.empty()) {
        Node n(pq.top());
        pq.pop();

        if (board.isDiscovered(n.x, n.y)) {
            continue;
        }
        else if (board.isEnd(n.x, n.y)) {
            nodeGraph.emplace_front(n);
            return searched;
        }
        else if (!board.isWall(n.x, n.y) && !board.isStart(n.x, n.y)) {
            n.priority = n.parent->priority + 1;
            nodeGraph.emplace_front(n);
            add_children(board, nodeGraph.front());
            board.discover(n.x, n.y);
            board.display();
            searched++;
        }
    }
}
