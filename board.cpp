#include<iostream>
#include<vector>
#include"board.h"

Board::Board(int size){
    char baseAscii = 97;
    
    for (int i=0; i<size; i++){
        this->letters.push_back(baseAscii+i);
        this->numbers.push_back(i+1);
    }

    this->coordinates.init(size,size);
    this->visitedSquares.init(size,size);
};



