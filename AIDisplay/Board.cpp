#include "Board.h"
#include <chrono>

using std::cout;
using std::endl;

static const std::chrono::duration<double> FRAME(0.05);

std::vector<std::string> split_string(std::string input_string) {
    std::vector<std::string> splits;
    char separator = ' ';

    size_t i = 0;
    size_t pos = input_string.find(separator);

    while (pos != std::string::npos) {
        if (input_string.substr(i, pos - i) != BOARD_DELIM) {
            splits.push_back(input_string.substr(i, pos - i));
        }

        i = pos + 1;
        pos = input_string.find(separator, i);
    }

    if (input_string.substr(i, std::min(pos, input_string.length()) - i + 1) != BOARD_DELIM) {
        splits.push_back(input_string.substr(i, std::min(pos, input_string.length()) - i + 1));
    }

    return splits;
}

Board::Board()
{
}


Board::~Board()
{
}

// Load the board from file and set the starting position ({0, 0} as default)
void Board::load(char* fn)
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
    }

    start = findStart();
}

Node Board::findStart() 
{
    // Find the starting point (start at 0,0 if not specified).
    for (int i = 0; i < vertices.size(); ++i) {
        for (int j = 0; j < vertices[i].size(); ++j) {
            if (vertices[i][j] == BOARD_START)
                return { i, j };
        }
    }
    return { 0, 0 };
}

// Print the board
void Board::display() {
    std::stringstream ss;
    for (auto & v : vertices) {
        ss << "\t";
        for (auto & s : v) {
            if (s == ".")
                ss << "  ";
            else
                ss << s << " ";
        }
        ss << endl;
    }
    ss << endl << endl;
    cout << ss.str();

    // Quick hack for frame rate
    static std::chrono::high_resolution_clock::time_point last;
    if (std::chrono::high_resolution_clock::now() - last < FRAME) {
        std::this_thread::sleep_for(FRAME - (std::chrono::high_resolution_clock::now() - last));
    }
    last = std::chrono::high_resolution_clock::now();
}

void Board::clear() {
    for (auto & v : vertices) {
        for (auto & s : v) {
            if (s == BOARD_DISCOVERED)
                s = BOARD_UNDISCOVERED;
        }
    }
}
