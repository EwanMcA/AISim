#include "Dfs.h"

unsigned int Dfs::recurse(Node& n) {
    if (board.isDiscovered(n.x, n.y) || board.isWall(n.x, n.y)) {
        return 0;
    }
    else if (board.isEnd(n.x, n.y)) {
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

unsigned int Dfs::run() {
    nodeGraph.emplace_front(board.findStart());
    return recurse(nodeGraph.front()) - 1;
  
}