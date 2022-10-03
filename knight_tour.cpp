#include<iostream>
#include<vector>
#include<sstream>
#include<string>
#include<cstdlib>
#include"board.h"
#include"matrix.h"


void printVectors(std::vector<char> letters, std::vector<int> numbers);

void checkParams(chessMatrix<std::string> coordinates, std::string start, std::string end);

bool findKnightsTour(Board gameBoard, std::string start, std::string end);

std::vector<std::string> getKnightMoves(Board gameBoard, std::string start);

int getIndex(std::vector<char> letters, char start_x);


int main(int argc, char *argv[]){
    try {
        
        std::istringstream iss1(argv[1]);

        int size;
        iss1 >> size;

    
        if (argc != 4 || size > 26){
            throw std::runtime_error("invalid parameter list");
        }

        std::istringstream iss2(argv[2]);
        std::istringstream iss3(argv[3]);

        std::string start, end;
        iss2 >> start;
        iss3 >> end; 

        Board gameBoard(size);

        gameBoard.coordinates.initChessSquares(gameBoard.letters, gameBoard.numbers);
        gameBoard.visitedSquares.allFalse();
        
        checkParams(gameBoard.coordinates, start, end);
        bool isTour = findKnightsTour(gameBoard, start, end);
        std::cout << "Tour is: " << isTour << "\n";

    
    }
    
    catch (std::runtime_error& excpt){
        std::cout << std::endl;
        std::cout << "Error: ";
        std::cout << excpt.what() << std::endl;
    }
    return 0;
}



void printVectors(std::vector<char> letters, std::vector<int> numbers){

    for (int i=0; i<letters.size(); i++){
        std::cout << letters.at(i) << numbers.at(i) << "\n";
    }
    
}

void checkParams(chessMatrix<std::string> coordinates, std::string start, std::string end){

    if (!coordinates.isExists(start) || !coordinates.isExists(end)){

        throw std::runtime_error ("invalid parameter list");
    }

}

bool findKnightsTour(Board gameBoard, std::string start, std::string end){

    if (start == end) return true;
    
    std::vector<std::string> possibleKnightMoves = getKnightMoves(gameBoard, start);

    return false;
}


std::vector<std::string> getKnightMoves(Board gameBoard, std::string start){

    char start_x = start.at(0);
    int y = stoi(start.substr(1,1));
    int x = getIndex(gameBoard.letters, start_x);

    std::cout << "x : " << x << " y: " << y << "\n";
    
    if (x == -1){
        throw std::runtime_error ("Out of range square");
    }

    // TODO: Finish possible steps

    std::vector<int> xMoves = {x-2, x-2};
    std::vector<int> yMoves = {y-1, y+1};

    std::cout << "first: " << xMoves.at(0) << yMoves.at(0) << "second: " << xMoves.at(1) << yMoves.at(1) << "\n";

    std::vector<std::string> moves;
    return moves;
    
}

int getIndex(std::vector<char> letters, char start_x){

    for (int i=0; i<letters.size(); i++){
        if (letters.at(i) == start_x){
            return i;
        }
    }
    return -1;
}