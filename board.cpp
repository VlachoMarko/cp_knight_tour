#include<iostream>
#include<vector>
#include"board.h"

Board::Board(int size){
    char baseAscii = 97;
    
    for (int i=0; i<size; i++){
        this->letters.push_back(baseAscii+i);
        this->numbers.push_back(i+1);
    }
    
    this->size = size;
    this->coordinates.init(size);
    this->visitedSquares.init(size);
};



