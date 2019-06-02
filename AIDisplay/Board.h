#pragma once

#include "pch.h"

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
    bool load(const char* fn);

    // Displays the board
    void display();

    // Clears the board
    void clear();

    /**********************************************************************************
    Sets the character at a given position on the board, to the discovered symbol.

        int - X position to discover.
        int - Y position to discover.
    ***********************************************************************************/
    void discover(int x, int y) { if (!is_start(x, y)) vertices[x][y] = BOARD_DISCOVERED; }

    // Returns board size
    size_t size() { return vertices.size(); }

    /**********************************************************************************
    The following methods return bools representing the state of a particular vertex.

        int - X position on the board.
        int - Y position on the board.

        Returns:
            bool - True if the vertex is respectively Discovered/End/Start/Undiscovered/Wall.
    ***********************************************************************************/
    bool is_discovered  (int x, int y) { return is_on_board(x, y) && vertices[x][y] == BOARD_DISCOVERED; };
    bool is_end         (int x, int y) { return is_on_board(x, y) && vertices[x][y] == BOARD_END; };
    bool is_start       (int x, int y) { return is_on_board(x, y) && vertices[x][y] == BOARD_START; };
    bool is_undiscovered(int x, int y) { return is_on_board(x, y) && vertices[x][y] == BOARD_UNDISCOVERED; };
    bool is_wall        (int x, int y) { return is_on_board(x, y) && vertices[x][y] == BOARD_WALL; };

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

    // Start-point of the board (defaults to {0, 0})
    std::pair<int, int> start;
    // End-point of the board (defaults to {board.size(), board.size()})
    std::pair<int, int> end;

private:
    std::vector<std::vector<char>> vertices;

    // Splits the given string into a vector of meaningful chars
    std::vector<char> split_string(std::string input_string);

    // Pushes display row onto given stringstream
    void row_stream(std::stringstream& ss, std::vector<char> row);

    // Sets the start position of the board (defaults to {0, 0})
    void set_start();
    // Sets the end position of the board (defaults to {board.size(), board.size()})
    void set_end();

    static const char BOARD_DELIM = '|';
    static const char BOARD_DISCOVERED = '*';
    static const char BOARD_UNDISCOVERED = '.';
    static const char BOARD_END = 'e';
    static const char BOARD_START = 's';
    static const char BOARD_WALL = 'w';

#ifdef _WIN32
    static const char BOARD_DISPLAY_UNDISCOVERED = (char)250;
    static const char BOARD_DISPLAY_WALL = (char)254;
    static const char BOARD_HZ = (char)196;
    static const char BOARD_TOP_LEFT = (char)218;
    static const char BOARD_TOP_RIGHT = (char)191;
    static const char BOARD_VE = (char)179;
    static const char BOARD_BOTTOM_LEFT = (char)192;
    static const char BOARD_BOTTOM_RIGHT = (char)217;
#else
    static const char BOARD_DISPLAY_UNDISCOVERED = BOARD_UNDISCOVERED;
    static const char BOARD_DISPLAY_WALL = 'O';
    static const char BOARD_HZ = '-';
    static const char BOARD_TOP_LEFT = '/';
    static const char BOARD_TOP_RIGHT = '\\';
    static const char BOARD_VE = '|';
    static const char BOARD_BOTTOM_LEFT = BOARD_TOP_RIGHT;
    static const char BOARD_BOTTOM_RIGHT = BOARD_TOP_LEFT;
#endif
};

