#ifndef BOARD_H
#define BOARD_H
#include "matrix.h"

class Board {
public:
    Board(int size);
    int size;
    std::vector<char> letters;
    std::vector<int> numbers;
    Matrix<std::string> coordinates;
    Matrix<bool> visitedSquares;

};

#endif