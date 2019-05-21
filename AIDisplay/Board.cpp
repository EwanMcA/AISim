#include "Board.h"
#include <chrono>

using std::cout;
using std::endl;

typedef std::chrono::high_resolution_clock HRClock;
static const std::chrono::duration<double> FRAME(0.05);

// Load the board from file and set the starting position ({0, 0} as default)
void Board::load(char* fn)
{
    std::string line;
    std::ifstream fs;
    fs.open(fn);
    if (fs.is_open()) {
        while (std::getline(fs, line)) {
            cout << line << endl;
            vertices.push_back(splitString(line));
        }
        fs.close();
    }
    else {
        cout << "failed to open file: " << fn << endl;
    }

    set_end();
}

void Board::set_end()
{
    for (int i = 0; i < vertices.size(); ++i) {
        for (int j = 0; j < vertices[i].size(); ++j) {
            if (vertices[i][j] == BOARD_END) {
                end = { i, j };
            }
        }
    }
}

Node Board::findStart() 
{
    // Find the starting point (start at 0,0 if not specified).
    for (int i = 0; i < vertices.size(); ++i) {
        for (int j = 0; j < vertices[i].size(); ++j) {
            if (vertices[i][j] == BOARD_START) {
                return { i, j, nullptr, 0 };
            }
        }
    }
    return { 0, 0, nullptr, 0 };
}

// Print the board
void Board::display() {
    
    // Quick hack for frame rate
    static HRClock::time_point last;
    if (HRClock::now() - last < FRAME) {
        std::this_thread::sleep_for(FRAME - (HRClock::now() - last));
    }
    last = HRClock::now();

    std::stringstream ss;

    // clear the screen
    for (int i = 0; i < 16; ++i) ss << endl;

    for (auto & v : vertices) {
        ss << "\t";
        for (auto & s : v) {
            if (s == '.')
                ss << "  ";
            else
                ss << s << " ";
        }
        ss << endl;
    }

    cout << ss.str();
}

void Board::clear() {
    for (auto & v : vertices) {
        for (auto & c : v) {
            if (c == BOARD_DISCOVERED)
                c = BOARD_UNDISCOVERED;
        }
    }
}

std::vector<char> Board::splitString(std::string input_string) {
    std::vector<char> splits;
    const char separator = ' ';

    for (char& c : input_string) {
        if (c != separator && c != BOARD_DELIM)
            splits.push_back(c);
    }

    return splits;
}
