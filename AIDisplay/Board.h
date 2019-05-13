#pragma once

#include "stdafx.h"

#define BOARD_DELIM "|"
#define BOARD_DISCOVERED "*"
#define BOARD_END "e"
#define BOARD_START "s"
#define BOARD_WALL "O"
#define BOARD_UNDISCOVERED "."

struct Node {
    int x;
    int y;
    Node* parent;
};

class Board
{
public:
    Board();
    ~Board();

    void load(char* fn);
    void display();
    void clear();
    
    void discover(int x, int y) { if (!isStart(x, y)) vertices[x][y] = BOARD_DISCOVERED; }

    Node findStart();
    size_t size() { return vertices.size(); }
    bool isDiscovered  (int x, int y) { return vertices[x][y] == BOARD_DISCOVERED; };
    bool isEnd         (int x, int y) { return vertices[x][y] == BOARD_END; };
    bool isStart       (int x, int y) { return vertices[x][y] == BOARD_START; };
    bool isUndiscovered(int x, int y) { return vertices[x][y] == BOARD_UNDISCOVERED; };
    bool isWall        (int x, int y) { return vertices[x][y] == BOARD_WALL; };

private:
    std::vector<std::vector<std::string>> vertices;
    Node start;
};

