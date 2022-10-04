#include<iostream>
#include<vector>
#include<sstream>
#include<string>
#include<cstdlib>
#include<cassert>
#include"board.h"
#include"matrix.h"

void checkParams(Board board);

void initVars(std::vector<int>& startCoordinates, std::vector<int>& endCoordinates, Board& board);

bool findKnightsTour(Board board, std::vector<int> start, std::vector<int> end,  std::vector<std::string>& knight_tour);

std::vector<int> getPossibleMoves(std::vector<int> start);

int getIndex(std::vector<char> letters, char start_x);

std::vector<int> pushToMoves(int x, int y, std::vector<int>& moves, int operations);

std::vector<int> getIntCoordinates(Board board, std::string start);

std::string getStringCoordinates(Board board, int x, int y);

void printEndMessage(bool hasTour, std::vector<std::string> knight_tour);


int main(int argc, char *argv[]){
    try {
            int size;
            std::vector<int> startCoordinates;
            std::vector<int> endCoordinates;

            
            if (argc != 4){
                throw std::runtime_error("invalid parameter list");
            }

            std::istringstream param1(argv[1]);
            std::istringstream param2(argv[2]);
            std::istringstream param3(argv[3]);

            param1 >> size;
        
            if (size > 26){
                throw std::runtime_error("invalid parameter list");
            }

            Board chessBoard(size);

            param2 >> chessBoard.startStr;
            param3 >> chessBoard.endStr; 
            
            chessBoard.coordinates.initCoordinates(chessBoard.letters, chessBoard.numbers);
            
            checkParams(chessBoard);
            initVars(startCoordinates, endCoordinates, chessBoard);

            bool hasTour = findKnightsTour(chessBoard, startCoordinates, endCoordinates, chessBoard.knight_tour);
            printEndMessage(hasTour, chessBoard.knight_tour);
    
        }
    
    catch (std::runtime_error& excpt){
        std::cout << excpt.what() << std::endl;
    }
    return 0;
}

void checkParams(Board board){

    if (board.coordinates.notContains(board.startStr) || board.coordinates.notContains(board.endStr)){

        throw std::runtime_error ("invalid parameter list");
    }

}

// TODO: Switch x and y everywhere

bool findKnightsTour(Board board, std::vector<int> start, std::vector<int> end, std::vector<std::string>& knight_tour){

    if (start.at(0) == end.at(0) && start.at(1) == end.at(1)) return true;
    
    std::vector<int> possibleMoves = getPossibleMoves(start);

     for (int i=0; i<possibleMoves.size(); i++){
        int x = possibleMoves.at(i);
        int y = possibleMoves.at(i+1);

        if ((0 <= x && x < board.size) && (0 <= y && y < board.size)) { 

            if (board.visitedSquares.at(x,y)){
                i++;
                continue;
            }

            std::string coordinates = getStringCoordinates(board, x, y);
            knight_tour.push_back(coordinates);

            board.visitedSquares.loadTo(x, y, true);
            std::vector<int> newStart = {x, y};

            bool success = findKnightsTour(board, newStart, end, knight_tour);

            if (success) {
                return true;
            }
            else { 
                board.visitedSquares.loadTo(x,y,false);
                knight_tour.pop_back();
            }
        }

        i++;
    }

    return false;
}


std::vector<int> getPossibleMoves(std::vector<int> moves){

    int x = moves.at(0);
    int y = moves.at(1);
    moves.clear();
    
    for (int i=0; i<4; i++){
        pushToMoves(x, y, moves, i);
    }

    return moves;    
}

std::vector<int> getIntCoordinates(Board board, std::string start){
    
    int x = getIndex(board.letters, start.at(0));
    assert(x >= 0);
    int y = stoi(start.substr(1,start.size()-1))-1;
    assert (y >= 0);

    std::vector<int> ints; 
    ints.push_back(x);
    ints.push_back(y);

    return ints;
}

std::string getStringCoordinates(Board board, int x, int y){

    std::string coordinates = "";

    assert(x < 26 && y < 26);

    coordinates += board.letters.at(x);
    coordinates += std::to_string(y+1);

    return coordinates;
}

int getIndex(std::vector<char> letters, char letterToFind){

    for (int i=0; i<letters.size(); i++){
        if (letters.at(i) == letterToFind){
            return i;
        }
    }

    throw std::runtime_error("Could not find letter");
}

std::vector<int> pushToMoves(int x, int y, std::vector<int>& moves, int operation){

    switch (operation){
        case 0: 
            moves.push_back(x-1);
            moves.push_back(y-2);
            moves.push_back(x-2);
            moves.push_back(y-1);
        break;

        case 1:
            moves.push_back(x-1);
            moves.push_back(y+2);
            moves.push_back(x-2);
            moves.push_back(y+1);
        break;

        case 2:
            moves.push_back(x+1);
            moves.push_back(y+2);
            moves.push_back(x+2);
            moves.push_back(y+1);
        break;

        case 3:
            moves.push_back(x+1);
            moves.push_back(y-2);
            moves.push_back(x+2);
            moves.push_back(y-1);
        break;
    }

    return moves;
}

void printEndMessage(bool hasTour, std::vector<std::string> knight_tour){

    if (hasTour){
        for (int i=0; i<knight_tour.size(); i++){
        std::cout << knight_tour.at(i) << " ";
        }
    }
    else {
        std::cout << "could not find a knight's tour";
    }
}


void initVars(std::vector<int>& startCoordinates, std::vector<int>& endCoordinates, Board& board){
   
    board.knight_tour.push_back(board.startStr);
    startCoordinates = getIntCoordinates(board, board.startStr);
    endCoordinates = getIntCoordinates(board, board.endStr);
    
    board.visitedSquares.setAllFalse();
    board.visitedSquares.loadTo(startCoordinates.at(0), startCoordinates.at(1), true);
}
           