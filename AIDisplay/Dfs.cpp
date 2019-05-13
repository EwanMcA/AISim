#include "Dfs.h"

bool Dfs::recurse(Node& n) {
    if (board.isDiscovered(n.x, n.y) || board.isWall(n.x, n.y)) {
        return false;
    }
    else if (board.isEnd(n.x, n.y)) {
        return true;
    }
    board.discover(n.x, n.y);
    board.display();

    if (n.x < board.size() - 1) {
        nodeGraph.emplace_front(Node{ n.x + 1, n.y, &n });
        if (recurse(nodeGraph.front()))
            return true;
    }
    if (n.y < board.size() - 1) {
        nodeGraph.emplace_front(Node{ n.x, n.y + 1, &n });
        if (recurse(nodeGraph.front()))
            return true;
    }
    if (n.x > 0) {
        nodeGraph.emplace_front(Node{ n.x - 1, n.y, &n });
        if (recurse(nodeGraph.front()))
            return true;
    }
    if (n.y > 0) {
        nodeGraph.emplace_front(Node{ n.x, n.y - 1, &n });
        if (recurse(nodeGraph.front()))
            return true;
    }
    return false;
}

void Dfs::run() {
    nodeGraph.emplace_front(board.findStart());
    recurse(nodeGraph.front());
}