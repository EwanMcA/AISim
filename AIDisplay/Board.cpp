#include "pch.h"
#include "Board.h"
#include <chrono>

using std::cout;
using std::endl;

typedef std::chrono::high_resolution_clock HRClock;
static const std::chrono::duration<double> FRAME(0.05);

bool Board::load(const char* fn)
{
    std::string line;
    std::ifstream fs;
    fs.open(fn);
    if (fs.is_open()) {
        while (std::getline(fs, line)) {
            cout << line << endl;
            vertices.push_back(split_string(line));
        }
        fs.close();
    }
    else {
        cout << "failed to open file: " << fn << endl;
        return false;
    }

    set_endpoints();
    return true;
}

void Board::set_endpoints()
{
    start = { 0, 0 };
    end = { vertices.size(), vertices[0].size() };
    for (int i = 0; i < vertices.size(); ++i) {
        for (int j = 0; j < vertices[i].size(); ++j) {
            if (vertices[i][j] == BOARD_START) {
                start = { i, j };
            } 
            else if (vertices[i][j] == BOARD_END) {
                end = { i, j };
            }
        }
    }
}

void Board::row_stream(std::stringstream& ss, std::vector<char> row)
{
    ss << "\t" << BOARD_VE << " ";
    for (auto & s : row) {
        switch (s) {
            case BOARD_UNDISCOVERED:
                ss << BOARD_DISPLAY_UNDISCOVERED;
                break;
            case BOARD_WALL:
                ss << BOARD_DISPLAY_WALL;
                break;
            default:
                ss << s;
        }
        ss << " ";
    }
    ss << BOARD_VE << endl;
}

void Board::display() {
    
    // Quick hack for frame rate
    static HRClock::time_point last;
    if (HRClock::now() - last < FRAME) {
        std::this_thread::sleep_for(FRAME - (HRClock::now() - last));
    }
    last = HRClock::now();

    std::stringstream ss;

    // clear the terminal
    for (int i = 0; i < 16; ++i) ss << endl;

    // Display board top
    ss << "\t" << BOARD_TOP_LEFT;
    for (int i = 0; i <= vertices[0].size() * 2; ++i) ss << BOARD_HZ;
    ss << BOARD_TOP_RIGHT << endl;
    
    // Display board row
    for (auto & v : vertices) {
        row_stream(ss, v);
    }

    // Display board bottom
    ss << "\t" << BOARD_BOTTOM_LEFT;
    for (int i = 0; i <= vertices[0].size() * 2; ++i) ss << BOARD_HZ;
    ss << BOARD_BOTTOM_RIGHT << endl;

    // Print board
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

std::vector<char> Board::split_string(std::string input_string) {
    std::vector<char> splits;
    const char separator = ' ';

    for (char& c : input_string) {
        if (c != separator && c != BOARD_DELIM)
            splits.push_back(c);
    }

    return splits;
}
