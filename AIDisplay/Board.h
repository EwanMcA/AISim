#pragma once

#include "stdafx.h"

// Represents a vertex in the space of discovered board positions
class Node {
public:
    Node(int x, int y)
        : x(x), y(y) {}
    Node(int x, int y, const Node* parent)
        : x(x), y(y), parent(parent) {}
    Node(int x, int y, const Node* parent, double priority)
        : x(x), y(y), parent(parent), priority(priority) {}

    int x;
    int y;
    const Node* parent;
    double priority;
};

// Represents the map
class Board
{
public:
    Board() {}
    ~Board() {}

    /**********************************************************************************
    Loads the board from file and sets the starting position ({0, 0} as default).

        char* - Name of file to read from.
    ***********************************************************************************/
    void load(char* fn);

    // Displays the board
    void display();

    // Clears the board
    void clear();

    // Sets the end-point of the board
    void set_end();
    
    /**********************************************************************************
    Sets the character at a given position on the board, to the discovered symbol.

        int - X position to discover.
        int - Y position to discover.
    ***********************************************************************************/
    void discover(int x, int y) { if (!is_start(x, y)) vertices[x][y] = BOARD_DISCOVERED; }
    
    /**********************************************************************************
    Returns the starting point as a Node, ({0, 0} is default if start can't be found).

            Node - Starting point of game board.
    ***********************************************************************************/
    Node find_start();

    // Returns board size
    size_t size() { return vertices.size(); }

    /**********************************************************************************
    The following methods return bools representing the state of a particular vertex.

        int - X position on the board.
        int - Y position on the board.

        Returns:
            bool - True if the vertex is respectively Discovered/End/Start/Undiscovered/Wall.
    ***********************************************************************************/
    bool is_discovered  (int x, int y) { return vertices[x][y] == BOARD_DISCOVERED; };
    bool is_end         (int x, int y) { return vertices[x][y] == BOARD_END; };
    bool is_start       (int x, int y) { return vertices[x][y] == BOARD_START; };
    bool is_undiscovered(int x, int y) { return vertices[x][y] == BOARD_UNDISCOVERED; };
    bool is_wall        (int x, int y) { return vertices[x][y] == BOARD_WALL; };

    /**********************************************************************************
    Determines whether the given position is within the boundaries of the board.

        int - X position on the board.
        int - Y position on the board.

        Returns:
            bool - True if the given position is within the board, false otherwise.
    ***********************************************************************************/
    bool is_on_board(int x, int y) 
    { 
        return x >= 0 && y >= 0 && x < vertices.size() && y < vertices[0].size();
    }

    // End-point of the board
    std::pair<int, int> end;

private:
    std::vector<std::vector<char>> vertices;

    // Splits the given string into a vector of meaningful chars
    std::vector<char> split_string(std::string input_string);

    static const char BOARD_DELIM = '|';
    static const char BOARD_DISCOVERED = '*';
    static const char BOARD_UNDISCOVERED = '.';
    static const char BOARD_END = 'e';
    static const char BOARD_START = 's';
    static const char BOARD_WALL = 'O';
};

