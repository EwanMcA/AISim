#include "AStar.h"

double AStar::get_priority(Board& board, Node& parent, int x, int y)
{
    int dx = abs(board.end.first - x);
    int dy = abs(board.end.second - y);
    return parent.priority + 1.0 + (dx + dy - std::min(dx, dy)) * hScale;
}
