#include "IterativeSearch.h"

// In the base case of UCS the priority is equal to the cost to reach the given position
double IterativeSearch::get_priority(const Node& parent, int x, int y) {
    return parent.priority + 1;
}

// Adds all 8 adjacent nodes, including diagonals
void IterativeSearch::add_children(const Node& n) 
{
    for (int i = -1; i < 2; i += 2) {
        if (board.is_on_board(n.x + i, n.y))
            pq.push(Node(n.x + i, n.y, &n, get_priority(n, n.x + i, n.y)));
        if (board.is_on_board(n.x, n.y + i))
            pq.push(Node(n.x, n.y + i, &n, get_priority(n, n.x, n.y + i)));
        if (board.is_on_board(n.x + i, n.y - i))
            pq.push(Node(n.x + i, n.y - i, &n, get_priority(n, n.x + i, n.y - i)));
        if (board.is_on_board(n.x + i, n.y + i))
            pq.push(Node(n.x + i, n.y + i, &n, get_priority(n, n.x + i, n.y + i)));
    }
}

// Uniform Cost Search (iterative)
unsigned int IterativeSearch::run()
{
    pq = std::priority_queue<Node, std::deque<Node>, NodePriority>();
    nodeGraph.emplace_front(board.find_start());
    pq.push(nodeGraph.front());
    add_children(nodeGraph.front());
    int searched(0);

    while (!pq.empty()) {
        Node n(pq.top());
        pq.pop();

        if (board.is_discovered(n.x, n.y)) {
            continue;
        }
        else if (board.is_end(n.x, n.y)) {
            nodeGraph.emplace_front(n);
            return searched;
        }
        else if (!board.is_wall(n.x, n.y) && !board.is_start(n.x, n.y)) {
            n.priority = n.parent->priority + 1;
            nodeGraph.emplace_front(n);
            add_children(nodeGraph.front());
            board.discover(n.x, n.y);
            board.display();
            searched++;
        }
    }
    return searched;
}
