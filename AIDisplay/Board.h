#pragma once

#include "stdafx.h"

struct Node {
    int x;
    int y;
    Node* parent;
    double priority;
};

class Board
{
public:
    Board() {}
    ~Board() {}

    void load(char* fn);
    void display();
    void clear();
    void set_end();
    
    void discover(int x, int y) { if (!isStart(x, y)) vertices[x][y] = BOARD_DISCOVERED; }

    Node findStart();
    size_t size() { return vertices.size(); }
    bool isDiscovered  (int x, int y) { return vertices[x][y] == BOARD_DISCOVERED; };
    bool isEnd         (int x, int y) { return vertices[x][y] == BOARD_END; };
    bool isStart       (int x, int y) { return vertices[x][y] == BOARD_START; };
    bool isUndiscovered(int x, int y) { return vertices[x][y] == BOARD_UNDISCOVERED; };
    bool isWall        (int x, int y) { return vertices[x][y] == BOARD_WALL; };

    std::pair<int, int> end;

private:
    std::vector<std::vector<char>> vertices;

    std::vector<char> splitString(std::string input_string);

    static const char BOARD_DELIM = '|';
    static const char BOARD_DISCOVERED = '*';
    static const char BOARD_UNDISCOVERED = '.';
    static const char BOARD_END = 'e';
    static const char BOARD_START = 's';
    static const char BOARD_WALL = 'O';
};

