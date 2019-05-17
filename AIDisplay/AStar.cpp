#include "AStar.h"

double AStar::get_priority(Board& board, Node& parent, int x, int y)
{
        return parent.priority + 1.0 + sqrt(pow(board.end.first - x, 2.0) + pow(board.end.second - y, 2.0));
}

