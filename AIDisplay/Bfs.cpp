#include "Bfs.h"

// Add the children of the front node to the end of the queue
void add_children(const size_t& size, Node& n, std::queue<Node>& q) {

    if (n.x > 0) {
        q.push({ n.x - 1, n.y, &n });
    }
    if (n.y > 0) {
        q.push({ n.x, n.y - 1, &n });
    }
    if (n.x < size - 1) {
        q.push({ n.x + 1, n.y, &n });
    }
    if (n.y < size - 1) {
        q.push({ n.x, n.y + 1, &n });
    }
}

// Breadth first search (iterative)
unsigned int Bfs::run()
{
    std::queue <Node> q;
    nodeGraph.emplace_front(board.findStart());
    q.push(nodeGraph.front());
    add_children(board.size(), nodeGraph.front(), q);
    int searched(0);

    while (!q.empty()) {
        Node n(q.front());
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
            add_children(board.size(), nodeGraph.front(), q);
            board.discover(n.x, n.y);
            board.display();
            searched++;
        }
    }
}
