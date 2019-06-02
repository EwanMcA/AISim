#include "pch.h"
#include "Dfs.h"

// The number of nodes searched doubles as a flag to signify whether a nested call
// resulted in the end-point being found.
unsigned int Dfs::recurse(Node& n) {
    if (board.is_discovered(n.x, n.y) || board.is_wall(n.x, n.y)) {
        return 0;
    }
    else if (board.is_end(n.x, n.y)) {
        return 1;
    }
    board.discover(n.x, n.y);
    board.display();

    int searched(0);

    if (n.x < board.size() - 1) {
        nodeGraph.emplace_front(Node{ n.x + 1, n.y, &n });
        if ((searched = recurse(nodeGraph.front())) > 0)
            return ++searched;
    }
    if (n.y < board.size() - 1) {
        nodeGraph.emplace_front(Node{ n.x, n.y + 1, &n });
        if ((searched = recurse(nodeGraph.front())) > 0)
            return ++searched;
    }
    if (n.x > 0) {
        nodeGraph.emplace_front(Node{ n.x - 1, n.y, &n });
        if ((searched = recurse(nodeGraph.front())) > 0)
            return ++searched;
    }
    if (n.y > 0) {
        nodeGraph.emplace_front(Node{ n.x, n.y - 1, &n });
        if ((searched = recurse(nodeGraph.front())) > 0)
            return ++searched;
    }
    return 0;
}

// Subtract 1 from the total nodes searched, so that the start node isn't counted
unsigned int Dfs::run() {
    nodeGraph.emplace_front(Node{ board.start.first, board.start.second, nullptr, 0 });
    return recurse(nodeGraph.front()) - 1;
}