#ifndef BOARD_H
#define BOARD_H
#include "matrix.h"

class Board {
public:
    Board(int size);
    std::vector<char> letters;
    std::vector<int> numbers;
    chessMatrix<std::string> coordinates;
    chessMatrix<bool> visitedSquares;
    std::vector<std::string> knight_tour;

};

#endif